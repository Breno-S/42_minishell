/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:25:58 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/14 21:16:44 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	is_builtins(char *cmd)
{
	if (!ft_strcmp("echo", cmd))
		return (0);
	else if (!ft_strcmp("cd", cmd))
		return (0);
	else if (!ft_strcmp("pwd", cmd))
		return (0);
	else if (!ft_strcmp("export", cmd))
		return (0);
	else if (!ft_strcmp("unset", cmd))
		return (0);
	else if (!ft_strcmp("env", cmd))
		return (0);
	else if (!ft_strcmp("exit", cmd))
		return (0);
	return (1);
}
