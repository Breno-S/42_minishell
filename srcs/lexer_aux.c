/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:47:03 by brensant          #+#    #+#             */
/*   Updated: 2025/12/04 15:58:53 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"

void	handle_metachar(t_lexer *l, t_token **t)
{
	if (lexer_starts_with(l, "&&"))
		*t = token(TOKEN_AND, &l->content[l->cursor], 2);
	else if (lexer_starts_with(l, "||"))
		*t = token(TOKEN_OR, &l->content[l->cursor], 2);
	else if (lexer_starts_with(l, "<<"))
		*t = token(TOKEN_REDIR_HEREDOC, &l->content[l->cursor], 2);
	else if (lexer_starts_with(l, ">>"))
		*t = token(TOKEN_REDIR_APPEND, &l->content[l->cursor], 2);
	else if (lexer_starts_with(l, "|"))
		*t = token(TOKEN_PIPE, &l->content[l->cursor], 1);
	else if (lexer_starts_with(l, "<"))
		*t = token(TOKEN_REDIR_APPEND, &l->content[l->cursor], 1);
	else if (lexer_starts_with(l, ">"))
		*t = token(TOKEN_REDIR_OUTPUT, &l->content[l->cursor], 1);
	else if (lexer_starts_with(l, "("))
		*t = token(TOKEN_OPEN_PAREN, &l->content[l->cursor], 1);
	else if (lexer_starts_with(l, ")"))
		*t = token(TOKEN_CLOSE_PAREN, &l->content[l->cursor], 1);
	lexer_chop_char(l, (*t)->text_len);
}

static void	add_segment(t_lexer *l, t_token_word **t, char quote,
	size_t segment_size)
{
	t_seg_type	type;
	t_segment	*new;

	if (quote == '\'')
		type = SQUOTES;
	else if (quote == '\"')
		type = DQUOTES;
	else
		type = UNQUOTED;
	new = ft_gcfct_register_root(
			segment(type, &l->content[l->cursor - segment_size], segment_size),
			"temp");
	segment_add(*t, new);
}

static void	save_segment(t_lexer *l, t_token_word **t, char quote)
{
	size_t	segment_size;

	segment_size = 0;
	if (quote)
	{
		while (l->content[l->cursor] != quote && l->cursor < l->content_len)
		{
			lexer_chop_char(l, 1);
			(*t)->text_len++;
			segment_size++;
		}
	}
	else
	{
		while (!is_metachar(l->content[l->cursor])
			&& ft_strchr("\"\'", l->content[l->cursor]) == NULL
			&& l->cursor < l->content_len)
		{
			lexer_chop_char(l, 1);
			(*t)->text_len++;
			segment_size++;
		}
	}
	add_segment(l, t, quote, segment_size);
}

void	handle_word(t_lexer *l, t_token **t)
{
	char	quote;

	*t = ft_gc_calloc_root(1, sizeof(t_token_word), "temp");
	if (!*t)
		return ;
	(*t)->class = TOKEN_WORD;
	while (!is_metachar(l->content[l->cursor]) && l->cursor < l->content_len)
	{
		if ((*t)->text == 0)
			(*t)->text = &l->content[l->cursor];
		quote = 0;
		if (ft_strchr("\"\'", l->content[l->cursor]))
		{
			quote = l->content[l->cursor];
			lexer_chop_char(l, 1);
			(*t)->text_len++;
		}
		save_segment(l, (t_token_word **)t, quote);
		if (quote)
		{
			lexer_chop_char(l, 1);
			(*t)->text_len++;
		}
	}
}
