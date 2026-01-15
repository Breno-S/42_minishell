/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:23:28 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/15 17:41:04 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execsh.h>

int	ft_export(t_exec *exec, t_hash_env **hash_table, int fd)
{
	int		hash;
	char	*str;
	int		i;
	int		rtn;

	if (!exec->args[1])
		return (ft_print_export(hash_table, fd));
	i = 1;
	rtn = 0;
	while (exec->args[i])
	{
		hash = count_hash((char *)exec->args[i]);
		if (verify_valid_var(exec->args[i]))
		{
			rtn = 1;
			export_error(exec->args[i++]);
		}
		else
			str = ft_gcfct_register_root(ft_strdup(exec->args[i++]), "env");
		modify_var(str, hash, hash_table);
	}
	return (rtn);
}

// int	save_return(int rtn, t_hash_env **hash_table)
// {
// 	int		hash;
// 	char	*str;
// 	int		i;
// 	char	*str_rtn;

// 	i = 1;
// 	str = ft_gcfct_register_root(ft_itoa(rtn), "temp");
// 	if (!str)
// 		return (1);
// 	hash = count_hash((char *)exec->args[i]);
// 	if (verify_valid_var(exec->args[i]))
// 	{
// 		rtn = 1;
// 		export_error(exec->args[i++]);
// 	}
// 	else
// 		str = ft_gcfct_register_root(ft_strdup(exec->args[i++]), "env");
// 	modify_var(str, hash, hash_table);
// 	return (rtn);
// }

int	modify_var(char *str, int hash, t_hash_env **hash_table)
{
	t_hash_env	*n_hash;

	n_hash = NULL;
	if (str && change_env(hash, hash_table, &str))
	{
		n_hash = ft_hashnew(str, T_ENV);
		if (n_hash)
			ft_hashadd_back((t_hash_env **)&hash_table[hash], n_hash);
		else
		{
			perror("Minishell");
			return (1);
		}
	}
	else
		return (1);
	return (0);
}

int	verify_valid_var(char *var)
{
	int	rtn;
	int	i;

	if (!var)
		return (-1);
	rtn = 0;
	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (i == 0 && !ft_isalpha(var[i]))
			return (1);
		else if (i >= 1 && !(ft_isalnum(var[i]) || var[i] == '_'))
			return (1);
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
