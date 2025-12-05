/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:46:53 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/04 15:48:31 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

t_hash_env	*ft_hashnew(void *content, int type)
{
	t_hash_env	*new_node;
	int			i;

	new_node = ft_gc_calloc_root(1, sizeof(t_hash_env), "env");
	if (!new_node)
		return ((void *)0);
	new_node->content = (void *)content;
	new_node->type_var = type;
	i = ft_strchr(content, '=') - (char *)content;
	if (((char *)content)[i + 1])
		new_node->has_content = 1;
	return (new_node);
}
