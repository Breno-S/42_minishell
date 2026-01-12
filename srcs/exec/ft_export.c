/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:23:28 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/11 12:18:08 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execsh.h>

int	ft_export(t_exec *exec, t_hash_env **hash_table, int fd)
{
	int			hash;
	char		*str;
	int			i;
	t_hash_env	*n_hash;

	if (!exec->args[1])
		return (ft_print_export(hash_table, fd));
	i = 1;
	while (exec->args[i])
	{
		hash = count_hash((char *)exec->args[i]);
		str = ft_gcfct_register_root(ft_strdup(exec->args[i]), "env");
		if (change_env(hash, hash_table, &str))
		{
			n_hash = ft_hashnew(str, T_ENV);
			if (n_hash)
				ft_hashadd_back((t_hash_env **)&hash_table[hash], n_hash);
			else
				perror("Minishell");
		}
		i++;
	}
	return (0);
}

int	ft_remove_var(void *content, t_ext_list *root)
{
	t_list	*aux;

	if (!content || !root)
		return (1);
	aux = root->head;
	while (aux)
	{
		if (ft_to_gc_list(aux->content)->content == content)
		{
			ft_gc_rm_root(&root, aux);
			break ;
		}
		aux = aux->next;
	}
	return (0);
}

int	change_env(int hash, t_hash_env **hash_table, char **str)
{
	t_hash_env	*hash_env;
	int			len;

	hash_env = hash_table[hash];
	len = ft_strchr((char *)str[0], '=') - str[0];
	if (len < 0)
		len = ft_strlen(str[0]);
	while (hash_env)
	{
		if (!ft_strncmp(hash_env->content, str[0], len))
		{
			ft_remove_var(((t_hash_env *)hash_table[hash])->content,
				ft_gc_call_root("env")->lst);
			((t_hash_env *)hash_table[hash])->content = str[0];
			if (len != (int)ft_strlen(str[0])
				&& ((t_hash_env *)hash_table[hash])->content[len + 1])
				((t_hash_env *)hash_table[hash])->has_content = 1;
			else
				((t_hash_env *)hash_table[hash])->has_content = 0;
			return (0);
		}
		hash_env = hash_env->next;
	}
	return (1);
}
