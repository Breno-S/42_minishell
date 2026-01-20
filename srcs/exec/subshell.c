/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:06:10 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/20 12:58:49 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "parsesh.h"
#include "signalsh.h"

int	sub_fork(t_ast *ast, t_msh *exec, t_pids **pids)
{
	pid_t	*n_pid;
	int		i;

	i = 0;
	if (!ast->cmd && expand_atom(ast))
		ast->cmd->error = 1;
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
		sub_exec(ast, exec);
	close_fd_parent(ast->cmd, ast->chan_com);
	close_fds_tree(ast);
	ast->chan_com = 0;
	pids[0]->total++;
	pids[0]->pids = n_pid;
	return (0);
}

int	sub_exec(t_ast *ast, t_msh *exec)
{
	int	rtn;

	rtn = 1;
	if (ast->cmd->error)
	{
		close_fds_tree_cmd(ast);
		finish_tree(exec, rtn);
	}
	dup_sub(ast);
	rtn = exec_tree(ast->left, exec, NULL);
	close_fds_tree_cmd(ast);
	finish_tree(exec, rtn);
	exit(rtn);
}

void	dup_sub(t_ast *ast)
{
	if (ast->chan_com > 0 && ast->cmd->infile == -1)
		ast->cmd->infile = ast->chan_com;
	if (ast->cmd->outfile > 0)
	{
		if (dup2(ast->cmd->outfile, STDOUT_FILENO) == -1)
		{
			perror("\033[0;31mMinishell: dup2");
			ft_putstr_fd("\033[0m", 2);
			close_fds_tree_cmd(ast);
			finish_tree(NULL, 1);
		}
		close(ast->cmd->outfile);
		ast->cmd->outfile = -1;
	}
	if (ast->cmd->infile > 0)
	{
		if (dup2(ast->cmd->infile, STDIN_FILENO) == -1)
		{
			perror("\033[0;31mMinishell: dup2");
			ft_putstr_fd("\033[0m", 2);
			close_fds_tree_cmd(ast);
			finish_tree(NULL, 1);
		}
		ast->cmd->infile = -1;
	}
}

t_exec	*build_sub(t_ast *ast)
{
	t_exec	*exec_sub;

	exec_sub = ft_gc_calloc_root(1, sizeof(t_exec), "temp");
	if (!exec_sub)
		return (NULL);
	exec_sub->infile = -1;
	exec_sub->outfile = -1;
	if (ast->redirs && handle_redirects(ast->redirs, &exec_sub, ast))
	{
		ast->cmd = exec_sub;
		exec_sub->error = 1;
		return (exec_sub);
	}
	return (exec_sub);
}
