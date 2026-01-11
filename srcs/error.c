/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:23:23 by brensant          #+#    #+#             */
/*   Updated: 2026/01/11 19:48:44 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "errorsh.h"
#include "parsesh.h"

int	log_syntax_error(t_token *token)
{
	ft_putstr_fd("Madshell: syntax error near unexpected token `", 2);
	if (token->class != TOKEN_WORD && token->class != TOKEN_INVALID)
		ft_putstr_fd(token_to_str(token), 2);
	else
		ft_putstr_fd(ft_gcfct_register_root(
			ft_substr(token->text, 0, token->text_len), "temp"), 2);
	ft_putendl_fd("\'", 2);
	return (STATUS_ERROR_SYNTAX);
}

int	log_ambiguous_redir_error(char *error_src)
{
	ft_putstr_fd("Madshell: ", 2);
	ft_putstr_fd(error_src, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("ambiguous redirect", 2);
	return (STATUS_ERROR);
}

int	syntax_check(t_token *token_list)
{
	t_token *aux;

	aux = token_list;
	while (aux)
	{
		if (aux->class == TOKEN_INVALID)
		{
			log_syntax_error(aux);
			return (0);
		}
		aux = aux->next;
	}
	return (1);
}
