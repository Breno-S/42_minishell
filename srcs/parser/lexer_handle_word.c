/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:47:03 by brensant          #+#    #+#             */
/*   Updated: 2025/12/12 18:01:04 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"

static size_t	consume_inside_squotes(t_lexer *l, size_t *text_len)
{
	size_t	seg_len;

	*text_len += lexer_chop_chars(l, 1);
	seg_len = lexer_chop_til(l, "\'", l->str_len, text_len);
	lexer_chop_while(l, "\'", 1, text_len);
	return (seg_len);
}

static t_segment	*handle_cmd_subst(t_lexer *l, size_t *text_len)
{
	const char	*seg_start;
	size_t		seg_len;
	t_seg_type	type;

	*text_len += lexer_chop_chars(l, 2);
	seg_start = &l->str[l->idx];
	seg_len = 0;
	type = CMD_SPLIT + l->dquote_flag;
	while (l->cmd_lvl && l->idx < l->str_len)
		seg_len += lexer_chop_chars(l, 1);
	lexer_chop_while(l, ")", 1, text_len);
	*text_len += seg_len;
	return (segment(type, seg_start, seg_len));
}

static t_segment	*handle_var(t_lexer *l, size_t *text_len)
{
	t_seg_type	type;
	const char	*seg_start;
	size_t		seg_len;

	if (lexer_starts_with(l, "$("))
		return (handle_cmd_subst(l, text_len));
	*text_len += lexer_chop_chars(l, 1);
	seg_start = &l->str[l->idx];
	type = VAR_SPLIT + l->dquote_flag;
	if (ft_strchr("0123456789@*-#!?$", l->str[l->idx]))
		return (segment(type, seg_start,
				lexer_chop_while(l, "0123456789@*-#!?$", 1, text_len)));
	seg_len = lexer_chop_while(l, VAR_START_CHARS, 1, text_len);
	if (seg_len == 0)
	{
		seg_start--;
		seg_len++;
		type = LITERAL;
	}
	seg_len += lexer_chop_til(l, METACHARS "\"$\0", l->str_len, text_len);
	return (segment(type, seg_start, seg_len));
}

static t_segment	*handle_dquotes(t_lexer *l, size_t *text_len)
{
	const char	*seg_start;
	t_segment	*seg_list;

	seg_list = NULL;
	*text_len += lexer_chop_chars(l, 1);
	while (l->str[l->idx] != '\"' && l->idx < l->str_len)
	{
		seg_start = &l->str[l->idx];
		segment_add(&seg_list, segment(LITERAL, seg_start,
				lexer_chop_til(l, "$\"", l->str_len, text_len)));
		if (l->str[l->idx] == '$')
			segment_add(&seg_list, handle_var(l, text_len));
	}
	lexer_chop_while(l, "\"", 1, text_len);
	return (seg_list);
}

t_token	*handle_word(t_lexer *l)
{
	size_t		text_len;
	t_segment	*seg_list;
	const char	*seg_start;

	text_len = 0;
	seg_list = NULL;
	while (!ft_strchr(METACHARS, l->str[l->idx]) && l->idx < l->str_len)
	{
		seg_start = &l->str[l->idx];
		if (l->str[l->idx] == '\'')
			segment_add(&seg_list, segment(LITERAL, seg_start + 1,
					consume_inside_squotes(l, &text_len)));
		else if (l->str[l->idx] == '\"')
			segment_add(&seg_list, handle_dquotes(l, &text_len));
		else if (l->str[l->idx] == '*')
			segment_add(&seg_list, segment(WILDCARD, seg_start,
					lexer_chop_while(l, "*", 1, &text_len)));
		else if (l->str[l->idx] == '$')
			segment_add(&seg_list, handle_var(l, &text_len));
		else
			segment_add(&seg_list, segment(LITERAL, seg_start, lexer_chop_til(l,
						METACHARS "\"\'*$", l->str_len, &text_len)));
	}
	return (token_word(&l->str[l->idx - text_len], text_len, seg_list));
}
