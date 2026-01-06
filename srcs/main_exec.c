/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:21:07 by brensant          #+#    #+#             */
/*   Updated: 2026/01/06 13:07:00 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "includes.h"
#include "parsesh.h"

int		handle_pipes(t_exec **exec);
int		exec_cmd(t_ast *ast, t_exec **exec);

int	main(int argc, char *argv[], char *envp[])
{
	t_hash_env	**hash_env;
	t_lexer		l;
	t_token		*token_list;
	t_parser	p;
	char		*line;
	t_ast		*ast;

	// t_exec		*exec;
	ft_gc_init();
	hash_env = (t_hash_env **)create_hash_env(envp, argv);
	while (1)
	{
		line = readline("Madshell> ");
		if (!line)
			break ;
		ft_gcfct_register(line, GC_DATA);
		add_history(line);
		l = lexer_new(line, ft_strlen(line));
		token_list = lexer_token_list(&l);
		p = parser_new(token_list);
		// printf("\n%s\n",glob_exp(token_list));
		ast = parser_parse(&p);
		handle_pre_exec(ast);
		// ft_printf("%s\n", handle_search("teste.sh"));
		// ft_printf("%s\n", handle_search("./teste.sh"));
		// ft_printf("%s\n", handle_search("ghhkjsdhf"));
		traverse_tree(ast, 0);
		ft_gc_del_root("temp");
		ft_gc_collect();
	}
	rl_clear_history();
	ft_gc_end();
}



// int	exec_cmd(t_ast *ast, t_exec **exec)
// {
// 	handle_pipes(exec);
// 	printf("oi");
// 	return (1);
// }

// int	handle_pipes(t_exec **exec)
// {
// 	t_list	*new;
// 	int		i;

// 	i = 0;
// 	if (!exec[0]->prev_fd)
// 		exec[0]->prev_fd = 1;
// 	else
// 		exec[0]->prev_fd = exec[0]->pipefd[0];
// 	if (pipe(exec[0]->pipefd) == -1)
// 	{
// 		perror("pipe");
// 		return (1);
// 	}
// 	while (i < 2)
// 	{
// 		new = ft_lstnew((void *)(long long)exec[0]->pipefd[i++]);
// 		if (!new)
// 			perror("pipe");
// 		if (!new)
// 			return (1);
// 		ft_lstadd_back(&exec[0]->all_fds, new);
// 	}
// 	return (0);
// }

// int	close_fds(t_fork info, int mode)
// {
// 	if (mode == ALL)
// 		if (info.fd[INFILE] != -1)
// 			close(info.fd[INFILE]);
// 	if (mode == PARENT)
// 	{
// 		close(info.pipefd[1]);
// 		if (info.old_stdout != -1)
// 			close(info.old_stdout);
// 	}
// 	else if (mode == CHILD || mode == ALL)
// 	{
// 		close(info.fd[OUTFILE]);
// 		close(info.pipefd[0]);
// 		close(info.pipefd[1]);
// 		close(info.old_stdout);
// 	}
// 	if (mode == PARENT && info.index == info.argc)
// 	{
// 		close(info.pipefd[0]);
// 		close(info.fd[OUTFILE]);
// 	}
// 	return (0);
// }

// int	open_files(t_fork *info, char **argv, int argc, t_file f_open)
// {
// 	if (!info->is_here_doc && f_open == OUTFILE)
// 		info->fd[OUTFILE] = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT,
// 				0644);
// 	else if (f_open == OUTFILE)
// 		info->fd[OUTFILE] = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT,
// 				0644);
// 	if (info->fd[OUTFILE] == -1 && f_open == OUTFILE)
// 	{
// 		perror("");
// 		return (1);
// 	}
// 	if (info->is_here_doc && f_open == INFILE)
// 		create_heredoc(argv[2], info);
// 	else if (f_open == INFILE)
// 		info->fd[INFILE] = open(argv[1], O_RDONLY);
// 	if (info->fd[INFILE] == -1 && f_open == INFILE)
// 	{
// 		perror("");
// 		return (1);
// 	}
// 	return (0);
// }
