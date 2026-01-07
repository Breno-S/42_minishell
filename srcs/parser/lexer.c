/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:59:17 by brensant          #+#    #+#             */
/*   Updated: 2026/01/06 21:32:20 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"

t_lexer	lexer_new(const char *str, size_t str_len)
{
	t_lexer	l;

	l.str = str;
	l.str_len = str_len;
	l.idx = 0;
	l.dquote_flag = 0;
	l.squote_flag = 0;
	l.cmd_lvl = 0;
	if (*str == '\"')
		l.dquote_flag = 1;
	else if (*str == '\'')
		l.squote_flag = 1;
	return (l);
}

int	lexer_starts_with(t_lexer *l, const char *prefix)
{
	size_t	prefix_len;
	size_t	i;

	prefix_len = ft_strlen(prefix);
	if (prefix_len == 0)
		return (1);
	if (l->idx + prefix_len - 1 >= l->str_len)
		return (0);
	i = 0;
	while (i < prefix_len)
	{
		if (prefix[i] != l->str[l->idx + i])
			return (0);
		i++;
	}
	return (1);
}

t_token	*handle_metachar(t_lexer *l)
{
	t_token	*t;

	t = NULL;
	if (lexer_starts_with(l, "&&"))
		t = token(TOKEN_AND, &l->str[l->idx], 2);
	else if (lexer_starts_with(l, "||"))
		t = token(TOKEN_OR, &l->str[l->idx], 2);
	else if (lexer_starts_with(l, "<<"))
		t = token(TOKEN_REDIR_HEREDOC, &l->str[l->idx], 2);
	else if (lexer_starts_with(l, ">>"))
		t = token(TOKEN_REDIR_APPEND, &l->str[l->idx], 2);
	else if (lexer_starts_with(l, "|"))
		t = token(TOKEN_PIPE, &l->str[l->idx], 1);
	else if (lexer_starts_with(l, "<"))
		t = token(TOKEN_REDIR_INPUT, &l->str[l->idx], 1);
	else if (lexer_starts_with(l, ">"))
		t = token(TOKEN_REDIR_OUTPUT, &l->str[l->idx], 1);
	else if (lexer_starts_with(l, "("))
		t = token(TOKEN_OPEN_PAREN, &l->str[l->idx], 1);
	else if (lexer_starts_with(l, ")"))
		t = token(TOKEN_CLOSE_PAREN, &l->str[l->idx], 1);
	else
		// ERROR: invalid token
	lexer_chop_chars(l, t->text_len);
	return (t);
}

t_token	*lexer_next(t_lexer *l)
{
	t_token	*t;

	t = NULL;
	lexer_chop_while(l, WHITESPACE, l->str_len, NULL);
	if (l->idx >= l->str_len)
		return (token(TOKEN_END, &l->str[l->idx], 1));
	if (ft_strchr(METACHARS, l->str[l->idx]))
		return (handle_metachar(l));
	else
		t = handle_word(l);
	return (t);
}

t_token	*lexer_token_list(t_lexer *l)
{
	t_token	*token_list;
	t_token	*t;

	token_list = NULL;
	t = lexer_next(l);
	while (t && t->class != TOKEN_END)
	{
		token_add(&token_list, t);
		t = lexer_next(l);
	}
	return (token_list);
}
