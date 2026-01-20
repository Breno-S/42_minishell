/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:21:07 by brensant          #+#    #+#             */
/*   Updated: 2026/01/20 15:36:44 by brensant         ###   ########.fr       */
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
	g_signal = 0;
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_signal_state;
	set_signal_interactive();
	msh->line = ft_gcfct_register_root(readline(PROMPT), "temp");
	if (isatty(STDIN_FILENO))
		rl_event_hook = NULL;
	if (g_signal)
	{
		save_return(130, msh->hash_env);
		return (2);
	}
	if (!msh->line)
	{
		if (isatty(STDIN_FILENO))
			ft_putendl_fd("exit", 2);
		finish_tree(NULL, 0);
		exit(0);
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
	save_return(2, msh->hash_env);
	return (0);
}

static int	parse_sh(t_msh *msh)
{
	t_parser	p;

	p = parser_new(msh->token_list);
	msh->ast = parser_parse(&p);
	if (msh->ast == NULL || p.idx->next)
	{
		log_syntax_error(p.idx);
		save_return(2, msh->hash_env);
		return (0);
	}
	return (1);
}

int	main(int argc __attribute__((unused)), char *argv[], char *envp[])
{
	t_msh	msh;

	ft_gc_init();
	msh.hash_env = (t_hash_env **)create_hash_env(envp, argv);
	while (1)
	{
		if (read_sh(&msh) == 1 && tokenize_sh(&msh) && parse_sh(&msh))
		{
			if (!open_heredoc_tree(msh.ast) && !g_signal)
			{
				build_aux_exec(&msh);
				if (msh.envp)
					save_return(exec_tree(msh.ast, &msh, NULL), msh.hash_env);
			}
			else if (g_signal)
			{
				save_return(130, msh.hash_env);
				close_heredoc(msh.ast);
			}
		}
		ft_gc_del_root("temp");
		ft_gc_collect();
	}
}
