/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:59:17 by brensant          #+#    #+#             */
/*   Updated: 2025/12/09 21:42:46 by brensant         ###   ########.fr       */
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
	if (*str == '"')
		l.dquote_flag = 1;
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

void	lexer_chop_char(t_lexer *l, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		l->idx++;
		i++;
		if (l->str[l->idx] == '"')
			l->dquote_flag = !l->dquote_flag;
	}
}

t_token	*lexer_next(t_lexer *l)
{
	t_token	*t;

	t = NULL;
	lexer_trim_left(l);
	if (l->idx >= l->str_len)
		return (token(TOKEN_END, &l->str[l->idx], 1));
	if (is_metachar(l->str[l->idx]))
		handle_metachar(l, &t);
	else
		handle_word(l, &t);
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
