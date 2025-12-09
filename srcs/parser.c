/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:54:22 by brensant          #+#    #+#             */
/*   Updated: 2025/12/08 23:11:22 by brensant         ###   ########.fr       */
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

t_ast	*parser_parse(t_parser *p)
{
	t_ast	*ast;

	ast = parse_cond(p);
	return (ast);
}
