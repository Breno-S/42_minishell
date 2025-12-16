/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:12:03 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/16 16:10:44 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

t_hash_env	**create_hash_env(char **arr, char **argv)
{
	t_hash_env		**hash_env;
	t_hash_env	*new;
	int			i;
	int			aux;
	char		*str;

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
		str[0] = ft_gcfct_register_root(ft_strjoin(str[2],arr[i++]), "env");
		if(!str)
			return (1);
		aux = count_hash(str[0]);
		new = ft_hashnew(str[0], T_ENV);
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
		if(!str)
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

int	count_hash(const char *var)
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

char	**ft_trim_env(char *envp, char sep, char *categ)
{
	char	**var;
	int		pos_sep;
	char	*chr;

	var = ft_gc_calloc(2, sizeof(char *), GC_DATA)->content;
	if (!var)
		return (NULL);
	chr = ft_strchr(envp, sep);
	if (!chr)
		chr = envp + ft_strlen(envp);
	pos_sep = chr - envp;
	var[0] = ft_gc_calloc_root(1, pos_sep + 1, categ);
	if (!var[0])
		return (NULL);
	ft_strlcpy(var[0], envp, pos_sep + 1);
	if (pos_sep == (int)ft_strlen(envp))
		var[1] = ft_gcfct_register_root(ft_strdup(""), categ);
	else
		var[1] = ft_gcfct_register_root(ft_strdup(&envp[pos_sep + 1]), categ);
	if (!var[1])
		return (NULL);
	return (var);
}
