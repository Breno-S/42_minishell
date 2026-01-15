/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:26:03 by brensant          #+#    #+#             */
/*   Updated: 2026/01/15 17:24:13 by rgomes-d         ###   ########.fr       */
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
	{
		log_syntax_error(p->idx);
		return (NULL);
	}
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
		if (!ast->right)
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
		if (!ast->right)
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
	{
		log_syntax_error(p->idx);
		return (NULL);
	}
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
