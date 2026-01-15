/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:21:07 by brensant          #+#    #+#             */
/*   Updated: 2026/01/15 17:53:38 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorsh.h"
#include "execsh.h"
#include "parsesh.h"
#include "signalsh.h"
#include "types.h"

int	g_signal;

static t_token	*tokenize(char *line)
{
	t_lexer l;

	l = lexer_new(line, ft_strlen(line));
	return (lexer_token_list(&l));
}

static t_ast	*parse(t_token *token_list)
{
	t_parser	p;

	p = parser_new(token_list);
	return (parser_parse(&p));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_msh	msh;

	t_hash_env	**hash_env;
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

		// READ LINE
		line = ft_gcfct_register_root(readline("Madshell> "), "temp");
		if (!line)
			ft_exit(NULL);
		add_history(line);

		// TOKENIZE
		l = lexer_new(line, ft_strlen(line));
		token_list = lexer_token_list(&l);
		syntax_check(token_list, &l);

		// GENERATE ABSTRACT SYNTAX TREE
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
