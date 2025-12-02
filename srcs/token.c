/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:51:43 by brensant          #+#    #+#             */
/*   Updated: 2025/12/01 21:12:25 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

t_token	token_new(void)
{
	t_token	t;

	t.class = TOKEN_END;
	t.text = NULL;
	t.text_len = 0;
	return (t);
}

const char	*token_class_name(t_token_class class)
{
	switch (class)
	{
		case TOKEN_END:
			return ("end of content");
		case TOKEN_INVALID:
			return ("invalid token");
		case TOKEN_WORD:
			return ("word");
		case TOKEN_PIPE:
			return ("pipe");
		case TOKEN_OPEN_PAREN:
			return ("open parenthesis");
		case TOKEN_CLOSE_PAREN:
			return ("close parenthesis");
		case TOKEN_STRING_SINGLE:
			return ("single quote string");
		case TOKEN_STRING_DOUBLE:
			return ("double quote string");
		case TOKEN_COMMENT:
			return ("comment");
		case TOKEN_REDIR_INPUT:
			return ("input redirection");
		case TOKEN_REDIR_OUTPUT:
			return ("output redirection");
		case TOKEN_REDIR_APPEND:
			return ("append redirection");
		case TOKEN_REDIR_HEREDOC:
			return ("heredoc");
		case TOKEN_AND:
			return ("AND");
		case TOKEN_OR:
			return ("OR");
		case TOKEN_WILDCARD:
			return ("WILDCARD");
	}
	return (NULL);
}
