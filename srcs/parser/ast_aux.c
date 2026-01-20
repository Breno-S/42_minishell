/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:09:24 by brensant          #+#    #+#             */
/*   Updated: 2026/01/20 15:50:47 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"
#include "errorsh.h"

int	parse_redirs(t_parser *p, t_ast *ast)
{
	t_token_class	type;
	t_token_word	*io_target;

	type = parser_peek(p);
	while (type >= TOKEN_REDIR_INPUT && type <= TOKEN_REDIR_HEREDOC)
	{
		parser_chop_token(p);
		if (parser_peek(p) != TOKEN_WORD)
			return (0);
		io_target = ft_gc_calloc_root(1, sizeof(*io_target), "temp");
		if (!io_target)
			return (0);
		ft_memcpy(io_target, p->idx, sizeof(*io_target));
		io_target->next = NULL;
		io_node_add(&ast->redirs, io_node(type, io_target));
		parser_chop_token(p);
		type = parser_peek(p);
	}
	return (1);
}

t_ast	*parse_atom(t_parser *p)
{
	if (parser_peek(p) == TOKEN_OPEN_PAREN)
	{
		if (!parser_chop_token(p))
			return (NULL);
		return (parse_sub(p));
	}
	else
		return (parse_cmd(p));
}
