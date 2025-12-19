/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinlst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:24:36 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/18 13:40:39 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_joinlst(t_list *aux)
{
	char	*str;
	char	*aux_j;

	str = NULL;
	while (aux)
	{
		if (!str)
			str = ft_strdup(aux->content);
		else
		{
			aux_j = ft_strjoin(str, " ");
			free(str);
			if (!aux_j)
				return (NULL);
			str = ft_strjoin(aux_j, aux->content);
			free(aux_j);
		}
		if (!str)
			return (NULL);
		aux = aux->next;
	}
	return (str);
}
