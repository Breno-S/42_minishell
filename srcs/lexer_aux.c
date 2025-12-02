/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:47:03 by brensant          #+#    #+#             */
/*   Updated: 2025/12/03 01:23:00 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"

static void	handle_two_metachar(t_lexer *l, t_token *t)
{
	if (lexer_starts_with(l, "&&"))
	{
		t->class = TOKEN_AND;
		t->text_len = 2;
	}
	else if (lexer_starts_with(l, "||"))
	{
		t->class = TOKEN_OR;
		t->text_len = 2;
	}
	else if (lexer_starts_with(l, "<<"))
	{
		t->class = TOKEN_REDIR_HEREDOC;
		t->text_len = 2;
	}
	else if (lexer_starts_with(l, ">>"))
	{
		t->class = TOKEN_REDIR_APPEND;
		t->text_len = 2;
	}
}

static void	handle_one_metachar(t_lexer *l, t_token *t)
{
	t->text_len = 1;
	if (lexer_starts_with(l, "|"))
		t->class = TOKEN_PIPE;
	else if (lexer_starts_with(l, "<"))
		t->class = TOKEN_REDIR_INPUT;
	else if (lexer_starts_with(l, ">"))
		t->class = TOKEN_REDIR_OUTPUT;
	else if (lexer_starts_with(l, "("))
		t->class = TOKEN_OPEN_PAREN;
	else if (lexer_starts_with(l, ")"))
		t->class = TOKEN_CLOSE_PAREN;
	else
		t->class = TOKEN_INVALID;
}

int	is_metachar(char c)
{
	if (ft_strchr(" \t\n|&()<>;", c))
		return (1);
	else
		return (0);
}

void	handle_metachar(t_lexer *l, t_token *t)
{
	handle_two_metachar(l, t);
	if (t->class == TOKEN_END)
		handle_one_metachar(l, t);
	if (t->class == TOKEN_END)
		handle_one_metachar(l, t);
	lexer_chop_char(l, t->text_len);
}

void	handle_string(t_lexer *l, t_token *t)
{
	char	quote;

	quote = l->content[l->cursor];
	t->text++;
	lexer_chop_char(l, 1);
	if (quote == '\"')
		t->class = TOKEN_STRING_DOUBLE;
	else
		t->class = TOKEN_STRING_SINGLE;
	while (l->content[l->cursor] != quote)
	{
		lexer_chop_char(l, 1);
		t->text_len++;
	}
	lexer_chop_char(l, 1);
}

void	handle_word(t_lexer *l, t_token *t)
{
	if (l->content[l->cursor] == '\"' || l->content[l->cursor] == '\'')
		handle_string(l, t);
	else
	{
		t->class = TOKEN_WORD;
		while (!is_metachar(l->content[l->cursor]) && ft_strchr("\"\'", l->content[l->cursor]) == NULL)
		{
			lexer_chop_char(l, 1);
			t->text_len++;
		}
	}
}
