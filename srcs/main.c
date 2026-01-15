/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:21:07 by brensant          #+#    #+#             */
/*   Updated: 2026/01/14 19:34:46 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorsh.h"
#include "execsh.h"
#include "parsesh.h"
#include "signalsh.h"
#include "types.h"

int	g_signal;

int	main(int argc, char *argv[], char *envp[])
{
	t_hash_env	**hash_env;
	t_lexer		l;
	t_parser	p;
	t_token		*token_list;
	t_ast		*ast;
	char		*line;
	t_aux_exec	*aux_exec;

	ft_gc_init();
	ft_printf("%d\n", getpid());
	hash_env = (t_hash_env **)create_hash_env(envp, argv);
	while (1)
	{
		g_signal = 0;
		set_signal_interactive();
		line = ft_gcfct_register_root(readline("Madshell> "), "temp");
		if (!line)
			ft_exit(NULL);
		add_history(line);
		l = lexer_new(line, ft_strlen(line));
		token_list = lexer_token_list(&l);
		if (syntax_check(token_list, &l))
		{
			p = parser_new(token_list);
			ast = parser_parse(&p);
			if (ast)
			{
				if (!open_heredoc_tree(ast) && !g_signal)
				{
					aux_exec = build_aux_exec(ast, hash_env);
					if (aux_exec)
						if (traverse_expand(ast, 0, hash_env))
							ft_putnbr_fd(exec_tree(ast, aux_exec, NULL), 0);
				}
				else
					close_heredoc(ast);
			}
		}
		ft_gc_del_root("temp");
		ft_gc_collect();
	}
}
