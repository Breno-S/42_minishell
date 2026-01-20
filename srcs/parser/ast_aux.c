/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:09:24 by brensant          #+#    #+#             */
/*   Updated: 2026/01/20 17:57:21 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"
#include "errorsh.h"

static int	add_arg(t_ast *ast, t_token_word *token)
{
	t_token_word	*arg;

	arg = ft_gc_calloc_root(1, sizeof(*arg), "temp");
	if (!arg)
		return (0);
	ft_memcpy(arg, token, sizeof(*arg));
	arg->next = NULL;
	token_add((t_token **)&ast->args, (t_token *)arg);
	return (1);
}

t_ast	*parse_cmd(t_parser *p)
{
	t_ast			*ast;
	t_token_class	class;

	ast = ft_gc_calloc_root(1, sizeof(*ast), "temp");
	if (!ast)
		return (NULL);
	ast->type = NODE_CMD;
	if (!parse_redirs(p, ast))
		return (NULL);
	class = parser_peek(p);
	if (class != TOKEN_WORD && class != TOKEN_NEWLINE)
		return (NULL);
	while (class == TOKEN_WORD)
	{
		add_arg(ast, (t_token_word *)p->idx);
		parser_chop_token(p);
		if (!parse_redirs(p, ast))
			return (NULL);
		class = parser_peek(p);
	}
	return (ast);
}

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
