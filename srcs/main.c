/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:21:07 by brensant          #+#    #+#             */
/*   Updated: 2026/01/12 23:03:49 by rgomes-d         ###   ########.fr       */
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
		line = ft_gcfct_register_root(readline("Madshell> "), "temp");
		if (!line)
			ft_exit(NULL);
		add_history(line);
		l = lexer_new(line, ft_strlen(line));
		token_list = lexer_token_list(&l);
		syntax_check(token_list);
		p = parser_new(token_list);
		ast = parser_parse(&p);
		aux_exec = build_aux_exec(ast, hash_env);
		if (aux_exec)
		{
			traverse_tree(ast, 0, hash_env);
			ft_putnbr_fd(exec_tree(ast, aux_exec, NULL), 0);
		}
		ft_gc_del_root("temp");
		ft_gc_collect();
	}
}

t_aux_exec	*build_aux_exec(t_ast *ast, t_hash_env **hash_table)
{
	char		**new_envp;
	t_aux_exec	*aux_exec;

	if (aux_print_export(hash_table, &new_envp))
	{
		perror("Minishell");
		return (NULL);
	}
	ft_gcfct_register((void *)new_envp, GC_DATA);
	aux_exec = ft_gc_calloc_root(1, sizeof(t_aux_exec), "temp");
	if (!aux_exec)
	{
		perror("Minishell");
		return (NULL);
	}
	aux_exec->envp = new_envp;
	aux_exec->hash_env = hash_table;
	aux_exec->head = ast;
	return (aux_exec);
}
