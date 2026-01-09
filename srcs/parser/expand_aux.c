/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 18:56:27 by brensant          #+#    #+#             */
/*   Updated: 2026/01/08 21:18:10 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"
#include "types.h"

static t_segment	*consume_literal_wildcard(t_segment **seg)
{
	t_segment	*new_seg_lst;
	t_segment	*head;

	new_seg_lst = NULL;
	head = *seg;
	while (head && (head->type == LITERAL || head->type == WILDCARD))
	{
		segment_add(&new_seg_lst,
			segment(head->type, head->text, ft_strlen(head->text)));
		head = head->next;
		*seg = (*seg)->next;
	}
	return (new_seg_lst);
}

static t_token	*handle_split_seg(t_segment *seg)
{
	t_lexer		l;
	size_t		text_len;
	t_segment	*new_segs;
	t_token		*new_tokens;

	new_segs = NULL;
	text_len = 0;
	l = lexer_new(seg->text, ft_strlen(seg->text));
	while (l.str[l.idx])
	{
		lexer_chop_while(&l, WHITESPACE, l.str_len, NULL);
		// if (l.idx >= l.str_len)
		// 	return (NULL);
		segment_add(&new_segs, segment(LITERAL, &l.str[l.idx], lexer_chop_til(&l, WHITESPACE, l.str_len, &text_len)));
		token_add(&new_tokens, token_word(new_segs->text, text_len, new_segs));
	}
	return (new_tokens);
}

t_token	*get_new_tokens(t_segment **seg)
{
	t_segment	*new_segs;
	t_token		*new_tokens;
	char		*text;

	new_segs = NULL;
	if ((*seg)->type == LITERAL || (*seg)->type == WILDCARD)
	{
		new_segs = consume_literal_wildcard(seg);
		text = text_from_segments(new_segs);
		return (token_word(text, ft_strlen(text), new_segs));
	}
	else
	{
		new_tokens = handle_split_seg(*seg);
		*seg = (*seg)->next;
	}
	return (new_tokens);
}

void	replace_tokens(t_token_word *target, t_token **prev,
	t_token *next, t_token **token_list)
{
	t_token		*new_tokens;
	t_segment	*seg;

	seg = target->seg_lst;
	while (seg)
	{
		new_tokens = get_new_tokens(&seg);
		if (new_tokens)
		{
			if (*prev)
				(*prev)->next = new_tokens;
			else
				*token_list = new_tokens;
			while (new_tokens->next)
				new_tokens = new_tokens->next;
			new_tokens->next = next;
			*prev = new_tokens;
		}
	}
}
