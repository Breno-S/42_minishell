/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:33:13 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/03 18:34:38 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_extadd_back(t_ext_list **lst, t_list *new)
{
	if (!lst[0] || !new)
		return ;
	new->next = NULL;
	if (!lst[0]->tail && !lst[0]->head)
	{
		new->prev = NULL;
		lst[0]->head = new;
		lst[0]->tail = new;
		return ;
	}
	new->prev = lst[0]->tail;
	lst[0]->tail->next = new;
	lst[0]->tail = new;
}
