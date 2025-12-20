/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:41:04 by brensant          #+#    #+#             */
/*   Updated: 2025/12/19 20:45:52 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "parsesh.h"

static void	remove_segment(t_segment *seg_lst, t_segment *target, t_segment *prev)
{
	if (prev)
		prev->next = target->next;
	else
		seg_lst = target->next;
}

static void	remove_null_segs(t_token_word *t)
{
	t_segment	*head;
	t_segment	*prev;

	head = t->seg_lst;
	prev = NULL;
	while (head)
	{
		if ((head->type >= 1 && head->type <= 4)
			&& (!head->text || head->text[0] == '\0'))
			remove_segment(t->seg_lst, head, prev);
		else 
			prev = head;
		head = head->next;
	}
}

static void join_fixed_segs(t_token_word *t)
{
	t_segment	*head;
	t_segment	*prev;

	head = t->seg_lst;
	prev = NULL;
	while (head->next)
	{
		if ((head->type == LITERAL || head->type == VAR_FIXED
				|| head->type == CMD_FIXED) && (head->next->type == LITERAL
					|| head->next->type == VAR_FIXED
					|| head->next->type == CMD_FIXED))
		{
				head->type = LITERAL;
				head->text = ft_gcfct_register_root(
					ft_strjoin(head->text, head->next->text), "temp");
				remove_segment(t->seg_lst, head->next, head);
				continue ;
		}
		else 
			prev = head;
		head = head->next;
	}
}

static void split_first_segs(t_token_word *t)
{
	t_segment	*head;
	t_segment	*prev;
	t_lexer		l;

	head = t->seg_lst;
	prev = NULL;
	while (head)
	{
		if (head->type == VAR_SPLIT || head->type == CMD_SPLIT)
		{
			l = lexer_new(head->text, ft_strlen(head->text));
			if (!ft_isspace(head->text[0]))
			{
				// create new first segment of LITERAL type
				size_t		lit_len;
				size_t		trim_len;
				char		*lit;
				t_segment	*new_seg;

				lit_len = lexer_chop_til(&l, " ", l.str_len, NULL);
				lit = ft_gcfct_register_root(
					ft_substr(head->text, 0, lit_len), "temp");

				new_seg = ft_gc_calloc_root(1, sizeof(*new_seg), "temp");
				*new_seg = (t_segment){LITERAL, lit, head};

				// add new literal segment before current segment
				if (prev)
					prev->next = new_seg;
				else
					t->seg_lst = new_seg;

				// trim this word and proceding spaces from current segment
				trim_len = lexer_chop_while(&l, " ", l.str_len, NULL);
				head->text = ft_substr(head->text, lit_len + trim_len,
					l.str_len);
				if (head->text[0] == '\0')
					new_seg->next = head->next;
				prev = head;
			}
		}
		else 
			prev = head;
		head = head->next;
	}
}

static void split_last_segs(t_token_word *t)
{
	t_segment	*head;
	t_segment	*prev;

	head = t->seg_lst;
	prev = NULL;
	while (head)
	{
		if (head->type == VAR_SPLIT || head->type == CMD_SPLIT)
		{
			if (!ft_isspace(head->text[ft_strlen(head->text) - 1]))
			{
				// create following segment of LITERAL type
				size_t		lit_len;
				size_t		trim_len;
				char		*lit;
				t_segment	*new_seg;
				char		*last_space;

				last_space = ft_strrchr(head->text, ' ');
				lit_len = ft_strlen(head->text);
				if (!last_space && head->next)
				{
						head->next->text = ft_gcfct_register_root(
						ft_strjoin(head->text, head->next->text), "temp");
						remove_segment(t->seg_lst, head, prev);
				}
				else if (last_space)
				{
					lit_len = &head->text[lit_len - 1] - last_space;
					lit = ft_gcfct_register_root(
						ft_substr(last_space, 1, lit_len), "temp");

					new_seg = ft_gc_calloc_root(1, sizeof(*new_seg), "temp");
					*new_seg = (t_segment){LITERAL, lit, head->next};

					// add new literal segment after current segment
					head->next = new_seg;

					// trim this word and preceding spaces from current segment
					head->text = ft_gcfct_register_root(ft_substr(head->text, 0, last_space - head->text), "temp");
					if (head->text[0] == '\0')
						remove_segment(t->seg_lst, head, prev);
				}
			}
		}
		else 
			prev = head;
		head = head->next;
	}
}

int	expand_token(t_token_word *t)
{
	t_segment	*seg;
	int			status;

	seg = t->seg_lst;
	status = 0;
	while (seg)
	{
		if (seg->type == VAR_FIXED || seg->type == VAR_SPLIT)
		{
			seg->text = var_exp(seg->text);
			status = 1;
		}
		else if (seg->type == CMD_FIXED || seg->type == CMD_SPLIT)
		{
			// TODO: expandir comando no subshell
			status = 1;
		}
		seg = seg->next;
	}
	return (status);
}

void	expand_token_list(t_token **token_list)
{
	t_token	*t;
	t_token	*prev;

	t = *token_list;
	prev = NULL;
	while (t)
	{
		if (t->class == TOKEN_WORD && expand_token((t_token_word *)t))
		{
			remove_null_segs((t_token_word *)t);
			split_first_segs((t_token_word *)t);
			split_last_segs((t_token_word *)t);
			join_fixed_segs((t_token_word *)t);
			// generate_new_tokens((t_token_word *)t);
		}
		else
			prev = t;
		t = t->next;
	}
}
