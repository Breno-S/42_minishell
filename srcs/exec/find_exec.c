/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:09:22 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/16 23:05:36 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

void	print_error_find(int type, char *arg, t_exec **exec)
{
	if (type == 1 || type == 2 || type == 3)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(arg, 2);
	}
	if (type == 1)
		ft_putendl_fd(": No such file or directory", 2);
	if (type == 2)
		ft_putendl_fd(": Is a directory", 2);
	if (type == 3)
		ft_putendl_fd(": Permission denied", 2);
	if (type == 4)
	{
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": command not found", 2);
	}
	if (type == 1 || type == 4)
		exec[0]->error = 127;
	else
		exec[0]->error = 126;
}

char	*handle_search(char *arg, t_exec **exec)
{
	char	**path;
	int		verify;

	path = find_path();
	if (ft_strchr(arg, '/') || !path)
	{
		verify = verify_file(arg);
		if (verify == 0)
			return (arg);
		else
			print_error_find(verify, arg, exec);
	}
	else
		return (find_executable(arg, path, exec));
	return (NULL);
}

char	*find_executable(char *arg, char **path, t_exec **exec)
{
	int		i;
	char	*str;
	char	*new_arg;
	int		verify;

	i = 0;
	new_arg = ft_gcfct_register_root(ft_strjoin("/", arg), "temp");
	while (path[i])
	{
		str = ft_gcfct_register_root(ft_strjoin(path[i], new_arg), "temp");
		verify = verify_file(str);
		if (verify == 0)
			return (str);
		else if (verify > 1)
		{
			print_error_find(verify, str, exec);
			return (NULL);
		}
		i++;
	}
	print_error_find(4, arg, exec);
	return (NULL);
}

char	**find_path(void)
{
	char	*var_path;
	char	**path;

	path = NULL;
	var_path = var_exp("PATH");
	if (var_path)
		path = ft_gcfct_arr_register_root((void **)ft_split(var_path, ':'),
				"temp");
	return (path);
}

int	verify_file(char *file)
{
	struct stat	path_stat;

	path_stat = (struct stat){0};
	if (access(file, F_OK))
		return (1);
	if (stat(file, &path_stat) == -1)
		return (1);
	if (S_ISDIR(path_stat.st_mode))
		return (2);
	if (access(file, X_OK))
		return (3);
	return (0);
}
