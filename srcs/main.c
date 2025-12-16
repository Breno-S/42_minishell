/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:21:07 by brensant          #+#    #+#             */
/*   Updated: 2025/12/16 12:47:53 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"
#include "execsh.h"
#include "types.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_hash_env	**hash_env;
	t_lexer		l;
	t_parser	p;
	t_token		*token_list;
	t_ast		*ast;
	char		*line;

	ft_gc_init();
	hash_env = (t_hash_env **)create_hash_env(envp);
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
