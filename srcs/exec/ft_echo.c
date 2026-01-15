/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:59:25 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/15 17:16:50 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	ft_echo(t_exec *cmd, int fd)
{
	int	i;
	int	func;
	int	flag;
	int	(*f[2])(char *, int);

	f[0] = ft_putstr_fd;
	f[1] = ft_putendl_fd;
	if (!cmd->args[1])
		return (0);
	i = verify_option(cmd->args);
	flag = 0;
	func = 0;
	if (i != 1)
		flag = 1;
	while (cmd->args[i])
	{
		if (cmd->args[i] && !cmd->args[i + 1] && !flag)
			func = 1;
		func[f](cmd->args[i], fd);
		i++;
		if (cmd->args[i])
			func[f](" ", fd);
	}
	return (0);
}

int	verify_option(char **args)
{
	int	i;
	int	y;

	i = 1;
	y = 2;
	while (args[i] && args[i][0] == '-')
	{
		y = 1;
		while (args[i][y])
		{
			if (args[i][y] != 'n')
				break ;
			y++;
		}
		if (args[i][y])
			break ;
		i++;
	}
	return (i);
}
