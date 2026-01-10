/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:07:18 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/09 20:59:59 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	ft_cd(t_exec *exec, t_hash_env *env)
{
	struct stat	status;
	int			i;

	status = (struct stat){0};
	i = 0;
	while (exec->args[i])
		i++;
	if (i > 2)
		return (cd_error(exec->args[1], 1));
	if (i == 1)
		return (cd_home(exec, env));
	if (stat(exec->args[1], &status) == -1)
		return (cd_error(exec->args[1], 3));
	if (!S_ISDIR(status.st_mode))
		return (cd_error(exec->args[1], 2));
	if (chdir(exec->args[1]) == -1)
		return (cd_error(exec->args[1], 3));
	return (0);
}

int	cd_error(char *arg, int type)
{
	if (type == 1)
		ft_putendl_fd("Minishell: cd: too many arguments", 2);
	else if (type == 2)
		ft_putendl_fd("Minishell: cd: Not a directory", 2);
	else if (type == 3)
	{
		ft_putstr_fd("Minishell: ", 2);
		perror(arg);
	}
	return (1);
}
