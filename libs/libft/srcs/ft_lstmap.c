/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:48:25 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/15 17:56:20 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ext_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*new;
	t_ext_list	*head;

	head = ft_calloc(1, sizeof(t_ext_list));
	if (!lst || !f || !del)
		return ((void *)0);
	new = ft_lstnew((f)(lst->content));
	if (!new)
		return ((void *)0);
	head->head = new;
	head->tail = new;
	lst = lst->next;
	while (lst)
	{
		ft_extadd_back(&head, ft_lstnew((f)(lst->content)));
		lst = lst->next;
	}
	return (head);
}
