/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:54:22 by brensant          #+#    #+#             */
/*   Updated: 2025/12/08 13:12:20 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"

t_parser	parser_new(t_token *token_list)
{
	t_parser	parser;

	parser.tokens = token_list;
	parser.idx = parser.tokens;
	return (parser);
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
		io_target = (t_token_word *)p->idx;
		io_node_add(&ast->redirs, io_node(type, io_target));
		parser_chop_token(p);
		type = parser_peek(p);
	}
	return (1);
}

static int	add_arg(t_ast *ast, t_token_word *token)
{
	t_token_word	*arg;

	arg = ft_gc_calloc_root(1, sizeof(*arg), "temp");
	if (!arg)
		return (0);
	ft_memcpy(arg, token, sizeof(*arg));
	arg->next = NULL;
	token_add(&ast->args, (t_token *)arg);
	return (1);
}

int	parse_exec(t_parser *p, t_ast *ast)
{
	t_token_class	type;

	if (!parse_redirs(p, ast))
		return (0);
	type = parser_peek(p);
	if (type == TOKEN_WORD)
	{
		if (ast->type != NODE_CMD)
			ast->type = NODE_CMD;
		while (type == TOKEN_WORD)
		{
			add_arg(ast, (t_token_word *)p->idx);
			parser_chop_token(p);
			parse_redirs(p, ast);
			type = parser_peek(p);
		}
	}
	parse_redirs(p, ast);
	return (1);
}

t_ast	*parser_parse(t_parser *p)
{
	t_ast	*ast;

	ast = ft_gc_calloc_root(1, sizeof(*ast), "temp");
	if (!ast)
		return (NULL);
	parse_exec(p, ast);
	return (ast);
}
