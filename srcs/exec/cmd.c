/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:16:59 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/14 21:16:44 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "signalsh.h"

int	fork_exec(t_exec *cmd, t_aux_exec *aux_exec, t_pids **pids, int chan_com)
{
	pid_t	*n_pid;
	int		i;

	i = 0;
	n_pid = ft_gc_calloc_root(pids[0]->total + 1, sizeof(pid_t *), "temp");
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
		exec(cmd, aux_exec, chan_com);
	close_fd_parent(cmd, chan_com);
	pids[0]->total++;
	pids[0]->pids = n_pid;
	return (0);
}

void	close_fd_parent(t_exec *cmd, int chan_com)
{
	if (!cmd)
		return ;
	if (cmd->infile > 2)
		close(cmd->infile);
	cmd->infile = -1;
	if (cmd->outfile > 2)
		close(cmd->outfile);
	cmd->outfile = -1;
	if (cmd->pipefd[0] > 2 && cmd->pipefd[1] != cmd->outfile)
	{
		close(cmd->pipefd[1]);
		cmd->pipefd[0] = 0;
		cmd->pipefd[1] = 0;
	}
	if (chan_com > 2)
		close(chan_com);
}

int	exec(t_exec *exec, t_aux_exec *aux_exec, int chan_com)
{
	if (exec->error)
		finish_tree(aux_exec, exec->error);
	if (dup_fds(exec))
		finish_tree(aux_exec, 1);
	close_fds_tree(aux_exec->head);
	if (chan_com > 0)
		close(chan_com);
	if (exec->cmd)
		execve(exec->cmd, exec->args, aux_exec->envp);
	if (!exec->cmd)
	{
		finish_tree(aux_exec, 0);
		exit(0);
	}
	perror("Minishell");
	finish_tree(aux_exec, 1);
	return (1);
}

int	dup_fds(t_exec *exec)
{
	if (exec->infile != -1)
	{
		if (dup2(exec->infile, STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
	}
	if (exec->outfile != -1)
	{
		if (dup2(exec->outfile, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
	}
	return (0);
}

int	handle_cmd(t_ast *ast, t_aux_exec *aux_exec, t_pids **pids)
{
	int	rtn;

	rtn = 1;
	if (!ast)
		return (rtn);
	if (ast->chan_com > 0 && ast->cmd->infile == -1)
	{
		ast->cmd->infile = ast->chan_com;
		ast->chan_com = 0;
	}
	if (ast->args)
		ast->cmd->cmd = handle_search(ast->args->seg_lst->text, &ast->cmd);
	rtn = fork_exec(ast->cmd, aux_exec, pids, ast->chan_com);
	ast->chan_com = 0;
	return (rtn);
}
