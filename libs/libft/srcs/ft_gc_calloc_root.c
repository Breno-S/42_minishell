/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_calloc_root.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:24:58 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/11/25 21:06:23 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Simular to original Calloc but allocs is inside of GC.
root: categ for data
*/
void	*ft_gc_calloc_root(size_t nmemb, size_t size, char *root)
{
	t_gc_list	*new;

	new = ft_gc_calloc(nmemb, size, GC_DATA);
	if (!new)
		return (NULL);
	ft_gc_register_root(new, root);
	return (new->content);
}
