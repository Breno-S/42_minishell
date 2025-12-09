/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:23:28 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/08 21:43:57 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execsh.h>

t_hash_env	*aux_unset(t_hash_env **hash_table, const char *var);
int			remove_env_root(void *arg, t_list *head);

int	ft_unset(t_hash_env **hash_table, const char *var)
{
	t_list		*env;
	char		*cmp;
	t_hash_env	*hash_env;
	int			count;

	env = ft_gc_call_root("env")->lst->head;
	count = count_hash((char *)var);
	if (!var)
		return (1);
	hash_env = aux_unset(hash_table, var);
	if (!hash_env)
		return (1);
	cmp = hash_env->content;
	if (hashpop(&hash_table[count], hash_env))
		return (1);
	remove_env_root(cmp, env);
	remove_env_root(hash_env, env);
	ft_gc_collect();
	return (0);
}

int	remove_env_root(void *arg, t_list *head)
{
	t_list	*env;

	env = head;
	while (env)
	{
		if (arg == ft_to_gc_list(env->content)->content)
		{
			ft_gc_rm_root(&ft_gc_call_root("env")->lst, env);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

t_hash_env	*aux_unset(t_hash_env **hash_table, const char *var)
{
	int			count;
	int			len;
	t_hash_env	*hash_env;

	if (!var)
		return (NULL);
	count = count_hash((char *)var);
	len = ft_strlen(var);
	hash_env = hash_table[count];
	while (hash_env)
	{
		if (!ft_strncmp(var, hash_env->content, len)
			&& (hash_env->content[len] == '=' || !hash_env->content[len]))
		{
			return (hash_env);
		}
		hash_env = hash_env->next;
	}
	return (NULL);
}
