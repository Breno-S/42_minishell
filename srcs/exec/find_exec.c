/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:09:22 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/06 19:04:19 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

void	print_error_find(int type, char *arg, t_exec **exec)
{
	if (type == 1)
	{
		ft_putstr_fd("Minishell: ", 0);
		perror(arg);
		exec[0]->error = 126;
	}
	if (type == 2)
	{
		ft_putstr_fd(arg, 0);
		ft_putendl_fd(": command not found", 0);
		exec[0]->error = 127;
	}
}

char	*handle_search(char *arg, t_exec **exec)
{
	char	**path;

	if (ft_strchr(arg, '/'))
	{
		if (access(arg, X_OK) == 0)
			return (arg);
		else if (errno == 13)
			print_error_find(1, arg, exec);
		else
			print_error_find(2, arg, exec);
	}
	else
	{
		path = find_path();
		if (!path)
			return (NULL);
		return (find_executable(arg, path, exec));
	}
	return (NULL);
}

char	*find_executable(char *arg, char **path, t_exec **exec)
{
	int		i;
	char	*str;
	char	*new_arg;

	i = 0;
	new_arg = ft_gcfct_register_root(ft_strjoin("/", arg), "temp");
	while (path[i])
	{
		str = ft_gcfct_register_root(ft_strjoin(path[i], new_arg), "temp");
		if (access(str, X_OK) == 0)
			return (str);
		else if (errno == 13)
		{
			print_error_find(1, str, exec);
			return (NULL);
		}
		i++;
	}
	print_error_find(2, arg, exec);
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
