/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 18:56:27 by brensant          #+#    #+#             */
/*   Updated: 2025/12/21 19:09:51 by brensant         ###   ########.fr       */
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

t_token	*get_new_tokens(t_segment **seg)
{
	t_segment	*new_segs;
	t_token		*new_tokens;
	char		*text;
	t_lexer		l;

	new_segs = NULL;
	if ((*seg)->type == LITERAL || (*seg)->type == WILDCARD)
	{
		new_segs = consume_literal_wildcard(seg);
		text = text_from_segments(new_segs);
		return (token_word(text, ft_strlen(text), new_segs));
	}
	else
	{
		l = lexer_new((*seg)->text, ft_strlen((*seg)->text));
		new_tokens = lexer_token_list(&l);
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
