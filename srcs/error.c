/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:23:23 by brensant          #+#    #+#             */
/*   Updated: 2026/01/07 20:17:45 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "errorsh.h"

int	log_syntax_error(char *near_token)
{
	ft_putstr_fd("Madshell: syntax error near unexpected token `", 2);
	ft_putstr_fd(near_token, 2);
	ft_putendl_fd("\'", 2);
	return (STATUS_ERROR_SYNTAX);
}

int	log_error(char *error_src, t_error_type error_type)
{
	if (error_type != ERR_CMD_NOT_FOUND)
	ft_putstr_fd("Madshell: ", 2);
	if (error_src)
	{
		ft_putstr_fd(error_src, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("ambiguous redirect", 2);
		return (STATUS_ERROR);
	}
	if (error_type == ERR_PERMISSION)
	{
		ft_putendl_fd("Permission denied", 2);
		return (STATUS_ERROR_PERMISSION);
	}
	else if (error_type == ERR_CMD_NOT_FOUND)
	{
		ft_putendl_fd("command not found", 2);
		return (STATUS_ERROR_CMD_NOT_FOUND);
	}
	else if (error_type == ERR_FILE_NOT_FOUND)
		ft_putendl_fd("No such file or directory", 2);
	else if (error_type == ERR_AMBIG_REDIR)
		ft_putendl_fd("ambiguous redirect", 2);
	return (STATUS_ERROR);
}
