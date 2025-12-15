/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:55:48 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/15 17:37:11 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"
#include "execsh.h"
#include "types.h"

int	main(void)
{
	t_lexer		l;
	t_parser	p;
	t_token		*token_list;
	t_ast		*ast;
	char		*line;

	ft_gc_init();
	while (1)
	{
		line = ft_gcfct_register(readline("Madshell> "), GC_DATA)->content;
		if (!line)
			break ;
		add_history(line);
		l = lexer_new(line, ft_strlen(line));
		token_list = lexer_token_list(&l);
		expand(token_list);
		p = parser_new(token_list);
		ast = parser_parse(&p);
		ft_gc_del_root("temp");
		ft_gc_collect();
	}
	rl_clear_history();
	ft_gc_end();
}
