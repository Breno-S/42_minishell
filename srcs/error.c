/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:23:23 by brensant          #+#    #+#             */
/*   Updated: 2026/01/17 18:47:39 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorsh.h"
#include "parsesh.h"
#include "execsh.h"

int	log_syntax_error(t_token *token)
{
	ft_putstr_fd("\033[0;31mMadshell: syntax error near unexpected token `", 2);
	if (token->class != TOKEN_WORD && token->class != TOKEN_INVALID)
		ft_putstr_fd(token_to_str(token), 2);
	else
		ft_putstr_fd(ft_gcfct_register_root(
				ft_substr(token->text, 0, token->text_len), "temp"), 2);
	ft_putendl_fd("\'\033[0m", 2);
	return (STATUS_ERROR_SYNTAX);
}

int	log_ambiguous_redir_error(char *error_src)
{
	ft_putstr_fd("\033[0;31mMadshell: ", 2);
	ft_putstr_fd(error_src, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("ambiguous redirect\033[0m", 2);
	return (STATUS_ERROR);
}

int	syntax_check(t_token *token_list, t_lexer *l)
{
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		if (aux->class == TOKEN_INVALID)
			log_syntax_error(aux);
		if (aux->class == TOKEN_INVALID)
			return (0);
		aux = aux->next;
	}
	if (l->dquote_flag || l->squote_flag)
	{
		ft_putstr_fd("\033[0;31m", 2);
		ft_putstr_fd(
			"Madshell: unexpected EOF while looking for matching `", 2);
		if (l->dquote_flag)
			ft_putendl_fd("\"'", 2);
		else
			ft_putendl_fd("\''", 2);
		ft_putendl_fd("Madshell: syntax error: unexpected end of file", 2);
		ft_putstr_fd("\033[0m", 2);
		return (0);
	}
	return (1);
}
