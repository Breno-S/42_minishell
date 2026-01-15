/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 18:35:55 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/15 19:28:33 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "signalsh.h"

int	handle_builtin(t_ast *ast, t_msh *exec, t_pids **pids)
{
	int	rtn;

	rtn = 1;
	if (ast->cmd->outfile == -1)
		ast->cmd->outfile = 1;
	if (pids[0]->type_head == NODE_PIPE)
		return (fork_builtin(ast->cmd, exec, pids, ast->chan_com));
	else if (pids[0]->type_head == NODE_CMD_BUILTIN)
	{
		if (ast->cmd->error)
		{
			close_fd_parent(ast->cmd, ast->chan_com);
			return (ast->cmd->error);
		}
		rtn = list_builtin(ast->cmd, exec);
		close_fd_parent(ast->cmd, ast->chan_com);
	}
	return (rtn);
}

int	list_builtin(t_exec *exec, t_msh *aux_exec)
{
	int	rtn;

	rtn = 1;
	if (!ft_strcmp("echo", exec->args[0]))
		rtn = ft_echo(exec, exec->outfile);
	else if (!ft_strcmp("cd", exec->args[0]))
		rtn = ft_cd(exec, aux_exec->hash_env);
	else if (!ft_strcmp("pwd", exec->args[0]))
		rtn = ft_pwd(exec->outfile);
	else if (!ft_strcmp("export", exec->args[0]))
		rtn = ft_export(exec, aux_exec->hash_env, exec->outfile);
	else if (!ft_strcmp("unset", exec->args[0]))
		rtn = ft_unset(exec, aux_exec->hash_env);
	else if (!ft_strcmp("env", exec->args[0]))
		rtn = ft_env(aux_exec->hash_env, exec->outfile);
	else if (!ft_strcmp("exit", exec->args[0]))
		rtn = ft_exit(aux_exec);
	if (aux_print_export(aux_exec->hash_env, &aux_exec->envp))
	{
		perror("Minishell");
		return (1);
	}
	ft_gcfct_register((void *)aux_exec->envp, GC_DATA);
	return (rtn);
}

int	fork_builtin(t_exec *cmd, t_msh *aux_exec, t_pids **pids, int chan_com)
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
		exec_builtin(cmd, aux_exec);
	close_fd_parent(cmd, chan_com);
	pids[0]->total++;
	pids[0]->pids = n_pid;
	return (0);
}

int	exec_builtin(t_exec *exec, t_msh *aux_exec)
{
	int	rtn;

	if (exec->error)
		finish_tree(aux_exec, exec->error);
	if (dup_fds(exec))
		finish_tree(aux_exec, 1);
	if (exec->outfile == -1)
		exec->outfile = 1;
	rtn = list_builtin(exec, aux_exec);
	close_fds_tree(aux_exec->ast);
	finish_tree(aux_exec, rtn);
	exit(rtn);
}
