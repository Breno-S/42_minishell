/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:54:22 by brensant          #+#    #+#             */
/*   Updated: 2026/01/20 15:49:45 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"
#include "errorsh.h"

t_parser	parser_new(t_token *token_list)
{
	t_parser	parser;

	parser.tokens = token_list;
	parser.idx = parser.tokens;
	parser.paren_flag = 0;
	return (parser);
}

static int	handle_parenthesis(t_parser *p)
{
	t_token_class	class;

	class = parser_peek(p);
	if (class == TOKEN_OPEN_PAREN)
	{
		if (p->paren_flag)
			return (0);
		else
			p->paren_flag =! p->paren_flag;
	}
	else if (class == TOKEN_CLOSE_PAREN)
	{
		if (!p->paren_flag)
			return (0);
		else
			p->paren_flag =! p->paren_flag;
	}
	return (1);
}

int	parser_chop_token(t_parser *p)
{
	int	status;

	if (!p || !p->idx)
		return (0);
	status = handle_parenthesis(p);
	p->idx = p->idx->next;
	return (status);
}

t_token_class	parser_peek(t_parser *p)
{
	if (!p || !p->idx)
		return (TOKEN_END);
	return (p->idx->class);
}

t_ast	*parser_parse(t_parser *p)
{
	t_ast	*ast;

	ast = parse_cond(p);
	return (ast);
}
