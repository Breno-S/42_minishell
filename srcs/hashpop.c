/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashpop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 21:35:37 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/08 21:41:44 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	hashpop(t_hash_env **head, t_hash_env *rm_hash)
{
	t_hash_env	*aux;

	if (!head[0] || !rm_hash)
		return (1);
	if (head[0] == rm_hash)
		head[0] = NULL;
	aux = head[0];
	while (aux)
	{
		if (aux->next == rm_hash)
		{
			aux->next = rm_hash->next;
			return (0);
		}
		aux = aux->next;
	}
	return (1);
}
