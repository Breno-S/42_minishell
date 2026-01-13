/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:23:23 by brensant          #+#    #+#             */
/*   Updated: 2026/01/13 20:26:47 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorsh.h"
#include "libft.h"

int	log_syntax_error(t_token *token)
{
	ft_putstr_fd("Madshell: syntax error near unexpected token `", 2);
	ft_putstr_fd(ft_gcfct_register_root(ft_substr(token->text, 0,
				token->text_len), "temp"), 2);
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

void	syntax_check(t_token *token_list)
{
	t_token	*aux;
	t_token	*prev;

	aux = token_list;
	prev = NULL;
	while (aux)
	{
		if (aux->class == TOKEN_INVALID)
		{
			log_syntax_error(aux);
			return ;
		}
		prev = aux;
		aux = aux->next;
	}
}
