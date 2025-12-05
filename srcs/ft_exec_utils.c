/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:24:08 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/04 17:39:57 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	export_env(char **arr)
{
	int		i;
	char	*str;

	i = 0;
	while (arr[i])
	{
		str = ft_gcfct_register_root(ft_strdup(arr[i++]), "env");
		if (!str)
			return (1);
	}
	return (0);
}

void	**create_hash_env(char **arr)
{
	void		**hash_env;
	t_hash_env	*new;
	int			i;
	int			aux;
	char		*str;

	i = 0;
	hash_env = ft_gc_calloc_root(256, sizeof(void *), "hash_env");
	if (!hash_env)
		return (NULL);
	while (arr[i])
	{
		str = ft_gcfct_register_root(ft_strdup(arr[i]), "env");
		aux = count_hash(arr[i]);
		new = ft_hashnew(str, T_ENV);
		if (hash_env[aux])
			ft_hashadd_back((t_hash_env **)&hash_env[aux], new);
		else
			hash_env[aux] = new;
		i++;
	}
	return (hash_env);
}

int	count_hash(char *var)
{
	int	rtn;
	int	i;

	if (!var)
		return (-1);
	rtn = 0;
	i = 0;
	while (var[i] && var[i] != '=')
		rtn = rtn + (var[i++] * 31);
	return (rtn % 256);
}

char	**create_envp_arg(t_list *env)
{
	t_gc_list	*envp_arr;
	t_root_list	*envp;
	int			i;

	i = 0;
	envp = ft_gc_call_root("envp");
	envp_arr = ft_gc_calloc(ft_lstsize(env) + 1, sizeof(char *), GC_DATA);
	if (!envp_arr)
		return (NULL);
	while (env)
	{
		((void **)envp_arr->content)[i] = ft_to_gc_list(env->content)->content;
		env = env->next;
		i++;
	}
	if (!envp)
		ft_gc_register_root(envp_arr, "envp");
	else
		envp->lst->head->content = envp_arr->content;
	return (envp_arr->content);
}

char	**ft_trim_env(char *envp, char sep)
{
	char	**var;
	int		pos_sep;

	var = ft_gc_calloc(2, sizeof(char *), GC_DATA)->content;
	if (!var)
		return (NULL);
	pos_sep = ft_strchr(envp, sep) - envp;
	var[0] = ft_gc_calloc(1, pos_sep + 1, GC_DATA)->content;
	if (!var[0])
		return (NULL);
	ft_strlcpy(var[0], envp, pos_sep + 1);
	var[1] = ft_gcfct_register(ft_strdup(&envp[pos_sep + 1]), GC_DATA)->content;
	if (!var[1])
		return (NULL);
	return (var);
}
