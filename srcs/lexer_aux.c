/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:47:03 by brensant          #+#    #+#             */
/*   Updated: 2025/12/07 20:22:20 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"

void	handle_metachar(t_lexer *l, t_token **t)
{
	if (lexer_starts_with(l, "&&"))
		*t = token(TOKEN_AND, &l->str[l->idx], 2);
	else if (lexer_starts_with(l, "||"))
		*t = token(TOKEN_OR, &l->str[l->idx], 2);
	else if (lexer_starts_with(l, "<<"))
		*t = token(TOKEN_REDIR_HEREDOC, &l->str[l->idx], 2);
	else if (lexer_starts_with(l, ">>"))
		*t = token(TOKEN_REDIR_APPEND, &l->str[l->idx], 2);
	else if (lexer_starts_with(l, "|"))
		*t = token(TOKEN_PIPE, &l->str[l->idx], 1);
	else if (lexer_starts_with(l, "<"))
		*t = token(TOKEN_REDIR_APPEND, &l->str[l->idx], 1);
	else if (lexer_starts_with(l, ">"))
		*t = token(TOKEN_REDIR_OUTPUT, &l->str[l->idx], 1);
	else if (lexer_starts_with(l, "("))
		*t = token(TOKEN_OPEN_PAREN, &l->str[l->idx], 1);
	else if (lexer_starts_with(l, ")"))
		*t = token(TOKEN_CLOSE_PAREN, &l->str[l->idx], 1);
	lexer_chop_char(l, (*t)->text_len);
}

static size_t	consume_inside_quotes(t_lexer *l, char quote, size_t *text_len)
{
	size_t	seg_len;

	seg_len = 0;
	lexer_chop_char(l, 1);
	*text_len += 1;
	while (l->str[l->idx] != quote && l->idx < l->str_len)
	{
		lexer_chop_char(l, 1);
		seg_len++;
		*text_len += 1;
	}
	if (l->str[l->idx] == quote)
	{
		lexer_chop_char(l, 1);
		*text_len += 1;
	}
	return (seg_len);
}

static size_t	consume_outside_quotes(t_lexer *l, size_t *text_len)
{
	size_t	seg_len;

	if (l->str[l->idx] == '*')
	{
		lexer_chop_char(l, 1);
		*text_len += 1;
		return (1);
	}
	seg_len = 0;
	while (!ft_strchr(" \t\n|&()<>;\"\'*", l->str[l->idx])
		&& l->idx < l->str_len)
	{
		lexer_chop_char(l, 1);
		seg_len++;
		*text_len += 1;
	}
	return (seg_len);
}

void	handle_word(t_lexer *l, t_token **t)
{
	size_t		text_len;
	t_segment	*seg_list;
	const char	*seg_start;

	text_len = 0;
	seg_list = NULL;
	seg_start = &l->str[l->idx];
	while (!is_metachar(l->str[l->idx]) && l->idx < l->str_len)
	{
		if (l->str[l->idx] == '\'')
			segment_add(&seg_list, segment(SQUOTES, seg_start + 1,
					consume_inside_quotes(l, '\'', &text_len)));
		else if (l->str[l->idx] == '\"')
			segment_add(&seg_list, segment(DQUOTES, seg_start + 1,
					consume_inside_quotes(l, '\"', &text_len)));
		else if (l->str[l->idx] == '*')
			segment_add(&seg_list, segment(UNQUOTED, seg_start,
					consume_outside_quotes(l, &text_len)));
		else
			segment_add(&seg_list, segment(UNQUOTED, seg_start,
					consume_outside_quotes(l, &text_len)));
		seg_start = &l->str[l->idx];
	}
	*t = token_word(&l->str[l->idx - text_len], text_len, seg_list);
}
