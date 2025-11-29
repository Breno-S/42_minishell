/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcfct_register_root.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:07:46 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/11/25 21:08:26 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Catch a pointer and alloc in GC.
root: categ for data
*/
void	*ft_gcfct_register_root(void *content, char *root)
{
	t_gc_list		*new;
	t_gcext_list	*lst;

	lst = ft_gc_start();
	if (!content || !lst)
		return (NULL);
	new = ft_calloc(1, sizeof(t_gc_list));
	if (!new)
	{
		free(content);
		return (NULL);
	}
	new->content = content;
	new->type = GC_DATA;
	ft_gclstadd_back(&lst, new);
	ft_gc_register_root(new, root);
	return (new->content);
}
