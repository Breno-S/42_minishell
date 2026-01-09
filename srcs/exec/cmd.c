/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:16:59 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/08 19:49:57 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	fork_exec(t_exec *cmd, char **envp, t_pids **pids)
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
		exec(cmd, envp);
	close_fd_parent(cmd);
	pids[0]->total++;
	pids[0]->pids = n_pid;
	return (0);
}

void	close_fd_parent(t_exec *cmd)
{
	if (!cmd)
		return ;
	if (cmd->infile->fd_tmp > 0)
		close(cmd->infile->fd_tmp);
	if (cmd->outfile->fd_tmp > 0)
		close(cmd->outfile->fd_tmp);
	if (cmd->pipefd[0] > 0 && cmd->pipefd[1] != cmd->outfile->fd_tmp)
		close(cmd->pipefd[1]);
}

int	exec(t_exec *exec, char **envp)
{
	if (exec->error)
	{
		ft_gc_end();
		exit(exec->error);
	}
	if (dup_fds(exec))
	{
		ft_gc_end();
		exit(1);
	}
	execve(exec->cmd, exec->args, envp);
	perror("Minishell");
	ft_gc_end();
	exit(1);
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
		else
			close(exec->infile->fd_tmp);
	}
	if (exec->outfile->fd_tmp != -1)
	{
		if (dup2(exec->outfile->fd_tmp, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
		else
			close(exec->outfile->fd_tmp);
	}
	return (0);
}

int	handle_cmd(t_ast *ast, char **envp, t_pids **pids)
{
	if (!ast)
		return (1);
	if (ast->chan_com > 0 && ast->cmd->infile->fd_tmp > 0)
		close(ast->chan_com);
	else if (ast->chan_com > 0 && ast->cmd->infile->fd_tmp == -1)
		ast->cmd->infile->fd_tmp = ast->chan_com;
	return (fork_exec(ast->cmd, envp, pids));
}
