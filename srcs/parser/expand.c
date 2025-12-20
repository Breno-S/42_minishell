/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:41:04 by brensant          #+#    #+#             */
/*   Updated: 2025/12/21 11:45:28 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "parsesh.h"

static void	split_before(t_segment *head, t_segment **prev, t_segment **seg_lst)
{
	size_t		lit_len;
	char		*lit;
	t_segment	*new_seg;
	t_lexer		l;

	l = lexer_new(head->text, ft_strlen(head->text));
	lit_len = lexer_chop_til(&l, " ", l.str_len, NULL);
	lit = ft_gcfct_register_root(
			ft_substr(head->text, 0, lit_len), "temp");
	new_seg = ft_gc_calloc_root(1, sizeof(*new_seg), "temp");
	*new_seg = (t_segment){LITERAL, lit, head};
	if (*prev)
		(*prev)->next = new_seg;
	else
		*seg_lst = new_seg;
	head->text = ft_substr(head->text, lit_len, l.str_len);
	*prev = head;
}

static void	split_after(t_segment *head)
{
	size_t		lit_len;
	char		*lit;
	t_segment	*new_seg;
	char		*last_space;

	last_space = ft_strrchr(head->text, ' ');
	lit_len = ft_strlen(head->text);
	if (last_space)
	{
		lit_len = &head->text[lit_len - 1] - last_space;
		lit = ft_gcfct_register_root(
				ft_substr(last_space, 1, lit_len), "temp");
		new_seg = ft_gc_calloc_root(1, sizeof(*new_seg), "temp");
		*new_seg = (t_segment){LITERAL, lit, head->next};
		head->next = new_seg;
		head->text = ft_gcfct_register_root(ft_substr(head->text, 0,
					-(head->text - (last_space + 1))), "temp");
	}
}

void	split_first_segs(t_token_word *t)
{
	t_segment	*head;
	t_segment	*prev;

	head = t->seg_lst;
	prev = NULL;
	while (head)
	{
		if (head->type == VAR_SPLIT || head->type == CMD_SPLIT)
		{
			if (!ft_isspace(head->text[0]))
				split_before(head, &prev, &t->seg_lst);
		}
		else
			prev = head;
		head = head->next;
	}
}

void	split_last_segs(t_token_word *t)
{
	t_segment	*head;

	head = t->seg_lst;
	while (head)
	{
		if (head->type == VAR_SPLIT || head->type == CMD_SPLIT)
		{
			if (!ft_isspace(head->text[ft_strlen(head->text) - 1]))
				split_after(head);
		}
		head = head->next;
	}
}

void	expand_token_list(t_token **token_list)
{
	t_token	*head;
	t_token	*prev;

	head = *token_list;
	prev = NULL;
	while (head)
	{
		if (head->class == TOKEN_WORD && expand_token((t_token_word *)head))
		{
			remove_null_segs((t_token_word *)head);
			split_first_segs((t_token_word *)head);
			split_last_segs((t_token_word *)head);
			join_fixed_segs((t_token_word *)head);
			replace_tokens((t_token_word *)head, &prev, head->next, token_list);
		}
		else
			prev = head;
		head = head->next;
	}
}
