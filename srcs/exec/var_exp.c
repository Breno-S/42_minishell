/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:32:25 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/14 21:16:44 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

char	*var_exp(const char *var_name)
{
	t_root_list	*hash_var;
	t_hash_env	**hash_table;
	t_hash_env	*aux;
	int			value_var;
	char		**var;

	hash_var = ft_gc_call_root("hash_env");
	if (!hash_var || !var_name)
		return (NULL);
	hash_table = ft_to_gc_list(hash_var->lst->head->content)->content;
	value_var = count_hash(var_name);
	aux = hash_table[value_var];
	while (aux)
	{
		var = ft_trim_env(aux->content, '=', "temp");
		if (!ft_strcmp(var_name, var[0]) && aux->type_var != T_SET)
			return (var[1]);
		aux = aux->next;
	}
	return (NULL);
}
