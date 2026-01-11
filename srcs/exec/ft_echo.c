/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:59:25 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/10 23:42:02 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	ft_echo(t_exec *cmd, int fd)
{
	int	i;
	int	func;
	int	(*f[2])(char *, int);

	f[0] = ft_putstr_fd;
	f[1] = ft_putendl_fd;
	i = 1;
	func = 0;
	if (!cmd->args[1])
		return (0);
	if (!ft_strcmp(cmd->args[i], "-n"))
		i++;
	while (cmd->args[i])
	{
		if (cmd->args[i] && !cmd->args[i + 1] && ft_strcmp(cmd->args[1], "-n"))
			func = 1;
		func[f](cmd->args[i], fd);
		i++;
		if (cmd->args[i])
			func[f](" ", fd);
	}
	return (0);
}
