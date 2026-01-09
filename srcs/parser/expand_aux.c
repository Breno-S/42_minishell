/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 18:56:27 by brensant          #+#    #+#             */
/*   Updated: 2026/01/09 14:35:33 by brensant         ###   ########.fr       */
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

static t_token	*lexer_next_dumb(t_lexer *l)
{
	const char	*text_start;
	size_t		text_len;
	t_segment	*seg;

	lexer_chop_while(l, WHITESPACE, l->str_len, NULL);
	if (l->idx >= l->str_len)
		return (token(TOKEN_END, &l->str[l->idx], 1));
	text_start = &l->str[l->idx];
	text_len = 0;
	seg = segment(LITERAL, text_start, lexer_chop_til(l, WHITESPACE, l->str_len,
				&text_len));
	return (token_word(seg->text, text_len, seg));
}

static t_token	*handle_split_seg(t_segment *seg)
{
	t_lexer		l;
	size_t		text_len;
	t_token		*t;
	t_token		*new_tokens;

	new_tokens = NULL;
	text_len = 0;
	l = lexer_new(seg->text, ft_strlen(seg->text));
	t = lexer_next_dumb(&l);
	while (t && t->class != TOKEN_END)
	{
		token_add(&new_tokens, t);
		t = lexer_next_dumb(&l);
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
