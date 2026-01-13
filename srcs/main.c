/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:21:07 by brensant          #+#    #+#             */
/*   Updated: 2026/01/13 20:34:42 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorsh.h"
#include "execsh.h"
#include "parsesh.h"
#include "types.h"

void		traverse_tree(t_ast *ast, int indent, t_hash_env **hash_env);

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
	hash_env = (t_hash_env **)create_hash_env(envp, argv);
	while (1)
	{
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
				open_heredoc_tree(ast);
				aux_exec = build_aux_exec(ast, hash_env);
				if (aux_exec)
				traverse_tree(ast, 0, hash_env);
				ft_putnbr_fd(exec_tree(ast, aux_exec, NULL), 0);
			}
		}
		ft_gc_del_root("temp");
		ft_gc_collect();
	}
}
