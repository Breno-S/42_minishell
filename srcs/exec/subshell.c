/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:06:10 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/15 17:16:50 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	sub_fork(t_ast *ast, t_aux_exec *exec, t_pids **pids)
{
	pid_t	*n_pid;
	int		i;

	i = 0;
	n_pid = ft_gc_calloc_root(pids[0]->total + 1, sizeof(pid_t *), "temp");
	if (ast->chan_com > 2)
		ast->left->chan_com = ast->chan_com;
	if (!n_pid)
		return (1);
	while (i < pids[0]->total)
	{
		n_pid[i] = pids[0]->pids[i];
		i++;
	}
	n_pid[i] = fork();
	set_signal_fork(n_pid[i]);
	if (!n_pid[i])
		sub_exec(ast, exec, pids);
	close_fd_parent(ast->cmd, ast->chan_com);
	ast->chan_com = 0;
	pids[0]->total++;
	pids[0]->pids = n_pid;
	return (0);
}

int	sub_exec(t_ast *ast, t_aux_exec *exec, t_pids **pids)
{
	int	rtn;

	rtn = 1;
	if (ast->cmd->pipefd[1] > 2)
	{
		if (dup2(ast->cmd->pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("Minishell: dup2");
			exit(1);
		}
		close(ast->cmd->pipefd[0]);
		close(ast->cmd->pipefd[1]);
	}
	rtn = exec_tree(ast->left, exec, NULL);
	finish_tree(exec, rtn);
	exit(rtn);
}
