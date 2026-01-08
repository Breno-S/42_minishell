/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:07:37 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/07 17:46:48 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	ft_print_export(t_hash_env **hash_table, int fd)
{
	int		count;
	char	**envs;
	int		i;

	if (!hash_table)
		return (-1);
	count = 1;
	if (aux_print_export(hash_table, &envs))
		return (1);
	sort_print(envs);
	i = 0;
	while (envs[i])
		ft_fix_print(envs[i++], fd);
	ft_gc_del_root("env_print");
	ft_gc_collect();
	free(envs);
	return (0);
}

int	ft_fix_print(char *env, int fd)
{
	char	**var;

	var = ft_trim_env(env, '=', "env_print");
	if (!var)
		return (1);
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(var[0], fd);
	ft_putstr_fd("=\"", fd);
	ft_putstr_fd(var[1], fd);
	ft_putendl_fd("\"", fd);
	return (0);
}

int	sort_print(char **envs)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	while (envs[i])
	{
		j = i + 1;
		while (envs[j])
		{
			if (ft_strcmp(envs[i], envs[j]) > 0)
			{
				aux = envs[j];
				envs[j] = envs[i];
				envs[i] = aux;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	aux_print_export(t_hash_env **hash_table, char ***envs)
{
	int			i[2];
	t_hash_env	*var;

	i[0] = 0;
	i[1] = 1;
	envs[0] = ft_calloc(i[1], 8);
	if (!envs[0])
		return (1);
	while (i[0] < 256)
	{
		var = hash_table[i[0]++];
		while (var)
		{
			if (var->type_var == T_ENV)
			{
				ft_realloc((void **)envs, i[1] + 1, 8, i[1] * 8);
				if (!envs[0])
					return (1);
				envs[0][i[1] - 1] = var->content;
				i[1]++;
			}
			var = var->next;
		}
	}
	return (0);
}
