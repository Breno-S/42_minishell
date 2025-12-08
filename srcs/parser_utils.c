/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 19:09:18 by brensant          #+#    #+#             */
/*   Updated: 2025/12/07 20:29:17 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"

void	parser_chop_token(t_parser *p)
{
	if (!p || !p->idx)
		return ;
	p->idx = p->idx->next;
}

t_token_class	parser_peek(t_parser *p)
{
	if (!p || !p->idx)
		return (TOKEN_END);
	return (p->idx->class);
}

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
