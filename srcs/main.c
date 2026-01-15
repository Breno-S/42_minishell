/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:21:07 by brensant          #+#    #+#             */
/*   Updated: 2026/01/15 20:39:31 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorsh.h"
#include "execsh.h"
#include "parsesh.h"
#include "signalsh.h"
#include "types.h"

int	g_signal;

static int	read_sh(t_msh *msh)
{
	set_signal_interactive();
	msh->line = ft_gcfct_register_root(readline("Madshell> "), "temp");
	if (!msh->line)
	{
		ft_exit(NULL);
		return (0);
	}
	add_history(msh->line);
	return (1);
}

static int	tokenize_sh(t_msh *msh)
{
	t_lexer	l;

	l = lexer_new(msh->line, ft_strlen(msh->line));
	msh->token_list = lexer_token_list(&l);
	if (syntax_check(msh->token_list, &l))
		return (1);
	return (0);
}

static int	parse_sh(t_msh *msh)
{
	t_parser	p;

	p = parser_new(msh->token_list);
	msh->ast = parser_parse(&p);
	if (msh->ast == NULL)
		return (0);
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_msh	msh;

	ft_gc_init();
	msh.hash_env = (t_hash_env **)create_hash_env(envp, argv);
	while (1)
	{
		g_signal = 0;
		set_signal_interactive();
		if (read_sh(&msh) && tokenize_sh(&msh) && parse_sh(&msh))
		{
			if (!open_heredoc_tree(msh.ast) && !g_signal)
			{
				build_aux_exec(&msh);
				if (msh.envp)
					if (traverse_expand(msh.ast, 0, msh.hash_env))
						save_return(exec_tree(msh.ast, &msh, NULL),
							msh.hash_env);
			}
			else
				close_heredoc(msh.ast);
		}
		ft_gc_del_root("temp");
		ft_gc_collect();
	}
}
