/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:22:01 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/19 14:08:14 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

t_hash_env	**create_hash_env(char **arr, char **argv)
{
	t_hash_env	**hash_env;
	int			i;

	i = 0;
	hash_env = ft_gc_calloc_root(256, sizeof(void *), "hash_env");
	if (!hash_env)
		return (NULL);
	import_argv(argv, hash_env);
	import_envp(arr, hash_env);
	return (hash_env);
}

int	import_argv(char **arr, t_hash_env **hash_env)
{
	int			i;
	int			aux;
	char		*str[3];
	t_hash_env	*new;

	i = 0;
	while (arr[i])
	{
		str[1] = ft_gcfct_register_root(ft_itoa(i), "temp");
		str[2] = ft_gcfct_register_root(ft_strjoin(str[1], "="), "temp");
		if (!str[1] || !str[2])
			return (1);
		str[0] = ft_gcfct_register_root(ft_strjoin(str[2], arr[i++]), "env");
		if (!str[0])
			return (1);
		aux = count_hash(str[0]);
		new = ft_hashnew(str[0], T_INTERNAL);
		if (!new)
			return (1);
		if (hash_env[aux])
			ft_hashadd_back(&hash_env[aux], new);
		else
			hash_env[aux] = new;
	}
	return (0);
}

int	import_envp(char **arr, t_hash_env **hash_env)
{
	int			i;
	int			aux;
	char		*str;
	t_hash_env	*new;

	i = 0;
	while (arr[i])
	{
		str = ft_gcfct_register_root(ft_strdup(arr[i]), "env");
		if (!str)
			return (1);
		aux = count_hash(arr[i]);
		new = ft_hashnew(str, T_ENV);
		if (!new)
			return (1);
		if (hash_env[aux])
			ft_hashadd_back(&hash_env[aux], new);
		else
			hash_env[aux] = new;
		i++;
	}
	return (0);
}
