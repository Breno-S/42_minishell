/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:07:18 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/10 17:42:41 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	ft_cd(t_exec *exec, t_hash_env **env)
{
	int	i;

	i = 0;
	while (exec->args[i])
		i++;
	if (i > 2)
		return (cd_error(exec->args[1], 1));
	if (i == 1)
		return (cd_special(env, 1));
	else if (!ft_strcmp(exec->args[1], "~"))
		return (cd_special(env, 3));
	else if (!ft_strcmp(exec->args[1], "-"))
		return (cd_special(env, 2));
	else
		return (cd_exec(exec->args[1], env));
}

int	cd_exec(char *new_path, t_hash_env **env)
{
	struct stat	status;

	status = (struct stat){0};
	if (stat(new_path, &status) == -1)
		return (cd_error(new_path, 3));
	if (!S_ISDIR(status.st_mode))
		return (cd_error(new_path, 2));
	if (update_pwd(1, env))
		return (1);
	if (chdir(new_path) == -1)
		return (cd_error(new_path, 3));
	if (update_pwd(2, env))
		return (1);
	return (0);
}

int	cd_special(t_hash_env **env, int type)
{
	char	*str;

	str = NULL;
	if (type == 1)
		str = var_exp("HOME");
	else if (type == 2)
		str = var_exp("OLDPWD");
	else if (type == 3)
		str = var_exp("~");
	if (!str && type == 1)
		return (cd_error("HOME", 4));
	else if (!str && type == 1)
		return (cd_error("HOME", 4));
	else if (!str && type == 1)
		return (cd_error("HOME", 4));
	else if (str)
		return (cd_exec(str, env));
	return (1);
}

int	update_pwd(int type, t_hash_env **hash_table)
{
	char	*str;
	int		rtn;

	rtn = aux_pwd(&str);
	if (rtn)
	{
		perror("Minishell");
		return (rtn);
	}
	if (type == 1)
		str = ft_gcfct_register_root(ft_strjoin("OLDPWD=", str), "env");
	else if (type == 2)
		str = ft_gcfct_register_root(ft_strjoin("PWD=", str), "env");
	if (!str)
	{
		perror("Minishell");
		return (1);
	}
	if (change_env(count_hash(str), hash_table, &str))
	{
		perror("Minishell");
		return (1);
	}
	return (0);
}

int	cd_error(char *arg, int type)
{
	if (type == 1)
		ft_putendl_fd("Minishell: cd: too many arguments", 2);
	else if (type == 2)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": Not a directory", 2);
	}
	else if (type == 3)
	{
		ft_putstr_fd("Minishell: ", 2);
		perror(arg);
	}
	else if (type == 4)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(" not set", 2);
	}
	return (1);
}
