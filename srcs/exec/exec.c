/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:33:11 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/07 15:16:41 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	pre_exec(t_ast *ast)
{
	int	rtn;

	rtn = 1;
	if (ast->type == NODE_CMD)
		rtn = handle_pre_exec(ast);
	else if (ast->type == NODE_AND)
		rtn = handle_pre_exec(ast);
	else if (ast->type == NODE_OR)
		rtn = handle_pre_exec(ast);
	else if (ast->type == NODE_PIPE)
		rtn = handle_pre_exec(ast);
	else if (ast->type == NODE_SUB)
		rtn = handle_pre_exec(ast);
	return (rtn);
}

int	exec(t_exec *exec, t_hash_env **hash_env)
{
	char	**envp;

	envp = ft_calloc(1, 8);
	aux_print_export(hash_env, &envp);
	if (!exec->cmd)
	{
		ft_gc_end();
		return (1);
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
