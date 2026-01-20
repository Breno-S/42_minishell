/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:26:03 by brensant          #+#    #+#             */
/*   Updated: 2026/01/20 18:29:49 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"
#include "errorsh.h"

inline static int	is_empty_atom(t_ast *ast)
{
	if (!ast)
		return (1);
	if (ast->type == NODE_CMD)
		return ((!ast->args && !ast->redirs));
	else if (ast->type == NODE_SUB)
		return (is_empty_atom(ast->left));
	return (0);
}

t_ast	*parse_pipe(t_parser *p)
{
	t_ast			*ast;
	t_ast			*cmd;

	ast = NULL;
	cmd = parse_atom(p);
	if (!cmd)
		return (NULL);
	if (parser_peek(p) == TOKEN_PIPE)
	{
		parser_chop_token(p);
		ast = ft_gc_calloc_root(1, sizeof(*ast), "temp");
		if (!ast)
			return (NULL);
		ast->type = NODE_PIPE;
		ast->left = cmd;
		ast->right = parse_pipe(p);
		if (is_empty_atom(ast->right))
			return (NULL);
	}
	else
		ast = cmd;
	return (ast);
}

t_ast	*parse_cond(t_parser *p)
{
	t_ast			*ast;
	t_ast			*cmd;
	t_token_class	class;

	ast = NULL;
	cmd = parse_pipe(p);
	if (!cmd)
		return (NULL);
	class = parser_peek(p);
	if (class == TOKEN_AND || class == TOKEN_OR)
	{
		parser_chop_token(p);
		ast = ft_gc_calloc_root(1, sizeof(*ast), "temp");
		if (!ast)
			return (NULL);
		ast->type = class - 10;
		ast->left = cmd;
		ast->right = parse_cond(p);
		if (is_empty_atom(ast->right))
			return (NULL);
	}
	else
		ast = cmd;
	return (ast);
}

t_ast	*parse_sub(t_parser *p)
{
	t_ast	*ast;
	t_ast	*sub_ast;

	p->paren_flag = 0;
	sub_ast = parse_cond(p);
	p->paren_flag = 1;
	if (!sub_ast)
		return (NULL);
	if (parser_peek(p) != TOKEN_CLOSE_PAREN)
		return (NULL);
	parser_chop_token(p);
	ast = ft_gc_calloc_root(1, sizeof(*ast), "temp");
	if (!ast)
		return (NULL);
	ast->type = NODE_SUB;
	ast->left = sub_ast;
	if (!parse_redirs(p, ast))
		return (NULL);
	return (ast);
}
