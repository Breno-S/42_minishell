/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:59:17 by brensant          #+#    #+#             */
/*   Updated: 2025/12/03 13:44:55 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"

t_lexer	lexer_new(const char *content, size_t content_len)
{
	t_lexer	l;

	l.content = content;
	l.content_len = content_len;
	l.cursor = 0;
	return (l);
}

int	lexer_starts_with(t_lexer *l, const char *prefix)
{
	size_t	prefix_len;
	size_t	i;

	prefix_len = ft_strlen(prefix);
	if (prefix_len == 0)
		return (1);
	if (l->cursor + prefix_len - 1 >= l->content_len)
		return (0);
	i = 0;
	while (i < prefix_len)
	{
		if (prefix[i] != l->content[l->cursor + i])
			return (0);
		i++;
	}
	return (1);
}

void	lexer_chop_char(t_lexer *l, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		l->cursor++;
		i++;
	}
}

void	lexer_trim_left(t_lexer *l)
{
	while (l->cursor < l->content_len && ft_isspace(l->content[l->cursor]))
		lexer_chop_char(l, 1);
}

t_token	*lexer_next(t_lexer *l)
{
	t_token	*t;

	t = NULL;
	lexer_trim_left(l);
	if (l->cursor >= l->content_len)
		return (token(TOKEN_END, &l->cursor[l->content], 1));
	if (is_metachar(l->content[l->cursor]))
		handle_metachar(l, &t);
	else
		handle_word(l, &t);
	return (t);
}
