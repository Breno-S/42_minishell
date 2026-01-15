/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:21:42 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/15 20:31:46 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	save_return(int rtn, t_hash_env **hash_table)
{
	int			hash;
	char		*str;
	t_hash_env	*n_hash;

	n_hash = NULL;
	str = ft_gcfct_register_root(ft_itoa(rtn), "temp");
	if (!str)
		return (1);
	str = ft_gcfct_register_root(ft_strjoin("?=", str), "env");
	if (!str)
		return (1);
	hash = count_hash(str);
	if (str && change_env(hash, hash_table, &str))
	{
		n_hash = ft_hashnew(str, T_INTERNAL);
		if (n_hash)
			ft_hashadd_back((t_hash_env **)&hash_table[hash], n_hash);
		else
		{
			perror("Minishell");
			return (1);
		}
	}
	return (0);
}
