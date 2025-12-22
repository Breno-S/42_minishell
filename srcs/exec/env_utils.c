/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:12:03 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/19 14:07:35 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

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
