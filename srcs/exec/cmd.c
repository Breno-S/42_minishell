/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:16:59 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/11 00:01:04 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	fork_exec(t_exec *cmd, t_aux_exec *aux_exec, t_pids **pids)
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
	if (!n_pid[i])
		exec(cmd, aux_exec);
	close_fd_parent(cmd);
	pids[0]->total++;
	pids[0]->pids = n_pid;
	return (0);
}

void	close_fd_parent(t_exec *cmd)
{
	if (!cmd)
		return ;
	if (cmd->infile->fd_tmp > 2)
	{
		close(cmd->infile->fd_tmp);
		cmd->infile->fd_tmp = -1;
	}
	if (cmd->outfile->fd_tmp > 2)
	{
		close(cmd->outfile->fd_tmp);
		cmd->outfile->fd_tmp = -1;
	}
	if (cmd->pipefd[0] > 2 && cmd->pipefd[1] != cmd->outfile->fd_tmp)
	{
		close(cmd->pipefd[1]);
		cmd->pipefd[0] = 0;
		cmd->pipefd[1] = 0;
	}
}

int	exec(t_exec *exec, t_aux_exec *aux_exec)
{
	if (exec->error)
		finish_tree(aux_exec, exec->error);
	if (dup_fds(exec))
		finish_tree(aux_exec, 1);
	close_fds_tree(aux_exec->head);
	execve(exec->cmd, exec->args, aux_exec->envp);
	perror("Minishell");
	finish_tree(aux_exec, 1);
	return (1);
}

int	dup_fds(t_exec *exec)
{
	if (exec->infile->fd_tmp != -1)
	{
		if (dup2(exec->infile->fd_tmp, STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
	}
	if (exec->outfile->fd_tmp != -1)
	{
		if (dup2(exec->outfile->fd_tmp, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
	}
	return (0);
}

int	handle_cmd(t_ast *ast, t_aux_exec *aux_exec, t_pids **pids)
{
	if (!ast)
		return (1);
	if (ast->chan_com > 0 && ast->cmd->infile->fd_tmp > 0)
	{
		close(ast->chan_com);
		ast->chan_com = 0;
	}
	else if (ast->chan_com > 0 && ast->cmd->infile->fd_tmp == -1)
		ast->cmd->infile->fd_tmp = ast->chan_com;
	return (fork_exec(ast->cmd, aux_exec, pids));
}
