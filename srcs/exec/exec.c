/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:33:11 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/07 21:30:14 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	exec_tree(t_ast *ast, char **envp, t_pids **pids)
{
	int		rtn;
	t_pids	*my_pids;
	int		i;

	rtn = 1;
	i = 0;
	if (!pids && ast->is_head == 0)
	{
		ast->is_head = 1;
		my_pids = ft_gc_calloc_root(1, sizeof(t_pids), "temp");
		pids = &my_pids;
	}
	if (ast->type == NODE_CMD && !ast->cmd->error)
		rtn = fork_exec(ast->cmd, envp, pids);
	else if (ast->type == NODE_CMD)
		rtn = ast->cmd->error;
	else if (ast->type == NODE_AND)
		pipe_exec(ast, envp, pids);
	else if (ast->type == NODE_OR)
		pipe_exec(ast, envp, pids);
	else if (ast->type == NODE_PIPE)
	{
		if (ast->is_head)
			pipe_exec(ast, envp, &my_pids);
		else
			pipe_exec(ast, envp, pids);
	}
	// else if (ast->type == NODE_SUB)
	// TODO: sub-shell
	if (ast->is_head)
		while (i < my_pids->total)
			rtn = waitpid((pid_t)my_pids->pids[i++], NULL, 0);
	return (rtn);
}

// TODO NODE_PIPE,
// TODO NODE_AND,
// TODO	NODE_OR,
// TODO	NODE_CMD,
// TODO	NODE_SUB,

int	pipe_exec(t_ast *ast, char **envp, t_pids **pids)
{
	int	rtn;

	rtn = 1;
	if (ast->left->type == NODE_AND || ast->left->type == NODE_OR)
		rtn = exec_tree(ast->left, envp, NULL);
	else
		rtn = exec_tree(ast->left, envp, pids);
	if (ast->right->type == NODE_AND || ast->left->type == NODE_OR)
		rtn = exec_tree(ast->right, envp, NULL);
	else
		rtn = exec_tree(ast->right, envp, pids);
	return (rtn);
}

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
	pids[0]->total++;
	pids[0]->pids = n_pid;
	return (0);
}

int	exec(t_exec *exec, char **envp)
{
	if (!exec->cmd)
	{
		ft_gc_end();
		exit(1);
	}
	if (exec->infile->fd_tmp != -1)
	{
		if (dup2(exec->infile->fd_tmp, STDIN_FILENO) == -1)
			perror("dup2");
		else
			close(exec->infile->fd_tmp);
	}
	if (exec->outfile->fd_tmp != -1)
	{
		if (dup2(exec->outfile->fd_tmp, STDOUT_FILENO) == -1)
			perror("dup2");
		else
			close(exec->outfile->fd_tmp);
	}
	execve(exec->cmd, exec->args, envp);
	perror("Minishell");
	ft_gc_end();
	exit(1);
}
