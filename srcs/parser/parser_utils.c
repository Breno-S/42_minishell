/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 19:09:18 by brensant          #+#    #+#             */
/*   Updated: 2026/01/09 16:23:39 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"

t_io_node	*io_node(t_token_class type, t_token_word *io_target)
{
	t_io_node	*io_node;

	if (!io_target
		|| !(type >= TOKEN_REDIR_INPUT && type <= TOKEN_REDIR_HEREDOC))
		return (NULL);
	io_node = ft_gc_calloc_root(1, sizeof(*io_node), "temp");
	if (!io_node)
		return (NULL);
	io_node->type = type;
	io_node->io_target = io_target;
	io_node->is_quoted_here = (io_node->type == TOKEN_REDIR_HEREDOC
			&& (ft_strchr((char *)io_node->io_target->text, '\"')
				|| ft_strchr((char *)io_node->io_target->text, '\'')));
	return (io_node);
}

void	io_node_add(t_io_node **io_node_list, t_io_node *new)
{
	t_io_node	*head;

	if (!io_node_list)
		return ;
	if (!*io_node_list)
		*io_node_list = new;
	else
	{
		head = *io_node_list;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}
