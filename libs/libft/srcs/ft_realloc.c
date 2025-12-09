/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 18:41:22 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/08 12:37:54 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void **mem, size_t nmemb, size_t size, size_t current_size)
{
	void	*new;

	new = ft_calloc(nmemb, size);
	if (!new)
	{
		free(mem[0]);
		return (NULL);
	}
	ft_memcpy(new, mem[0], current_size);
	free(mem[0]);
	mem[0] = new;
	return (new);
}
