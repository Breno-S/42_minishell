/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_join.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:10:00 by brensant          #+#    #+#             */
/*   Updated: 2026/01/16 23:50:01 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "parsesh.h"

static void	split_before(t_segment *curr, t_segment **prev, t_segment **seg_lst)
{
	size_t		lit_len;
	char		*lit;
	t_segment	*new_seg;
	t_lexer		l;

	l = lexer_new(curr->text, ft_strlen(curr->text));
	lit_len = lexer_chop_til(&l, " ", l.str_len, NULL);
	lit = ft_gcfct_register_root(
			ft_substr(curr->text, 0, lit_len), "temp");
	new_seg = ft_gc_calloc_root(1, sizeof(*new_seg), "temp");
	*new_seg = (t_segment){LITERAL, lit, curr};
	if (*prev)
		(*prev)->next = new_seg;
	else
		*seg_lst = new_seg;
	curr->text = ft_substr(curr->text, lit_len, l.str_len);
	*prev = curr;
}

static void	split_after(t_segment *curr)
{
	size_t		lit_len;
	char		*lit;
	t_segment	*new_seg;
	char		*last_space;

	last_space = ft_strrchr(curr->text, ' ');
	lit_len = ft_strlen(curr->text);
	if (last_space)
	{
		lit_len = &curr->text[lit_len - 1] - last_space;
		lit = ft_gcfct_register_root(
				ft_substr(last_space, 1, lit_len), "temp");
		new_seg = ft_gc_calloc_root(1, sizeof(*new_seg), "temp");
		*new_seg = (t_segment){LITERAL, lit, curr->next};
		curr->next = new_seg;
		curr->text = ft_gcfct_register_root(ft_substr(curr->text, 0,
					-(curr->text - (last_space + 1))), "temp");
	}
}

void	split_first_segs(t_token_word *token)
{
	t_segment	*seg;
	t_segment	*prev;

	seg = token->seg_lst;
	prev = NULL;
	while (seg)
	{
		if (seg->type == VAR_SPLIT || seg->type == CMD_SPLIT)
		{
			if (!ft_isspace(seg->text[0]))
			{
				if (ft_strrchr(seg->text, ' '))
					split_before(seg, &prev, &token->seg_lst);
				else
					seg->type = LITERAL;
			}
		}
		else
			prev = seg;
		seg = seg->next;
	}
}

void	split_last_segs(t_token_word *token)
{
	t_segment	*seg;

	seg = token->seg_lst;
	while (seg)
	{
		if (seg->type == VAR_SPLIT || seg->type == CMD_SPLIT)
		{
			if (!ft_isspace(seg->text[ft_strlen(seg->text) - 1]))
			{
				if (ft_strchr(seg->text, ' '))
					split_after(seg);
				else
					seg->type = LITERAL;
			}
		}
		seg = seg->next;
	}
}

void	join_fixed_segs(t_token_word *token)
{
	t_segment	*seg;

	seg = token->seg_lst;
	while (seg && seg->next)
	{
		if ((seg->type >= OUTSIDE && seg->type <= LITERAL)
			&& (seg->next->type >= OUTSIDE && seg->next->type <= LITERAL))
		{
			seg->type = LITERAL;
			seg->text = ft_gcfct_register_root(
					ft_strjoin(seg->text, seg->next->text), "temp");
			if (seg)
				seg->next = seg->next->next;
			else
				token->seg_lst = seg->next->next;
			continue ;
		}
		seg = seg->next;
	}
	if (seg && (seg->type >= OUTSIDE && seg->type <= CMD_FIXED))
		seg->type = LITERAL;
}
