/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:33:11 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/06 21:36:08 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	handle_pre_exec(t_ast *ast, t_hash_env **hash_env)
{
	t_exec	*exec_cmd;
	int		i;
	pid_t	teste;

	i = 0;
	exec_cmd = build_exec(ast);
	if (!exec_cmd)
		return (1);
	if (ast->redirs)
		handle_redirects(ast->redirs, &exec_cmd);
	exec_cmd->cmd = handle_search(ast->args->seg_lst->text, &exec_cmd);
	if (!exec_cmd->cmd)
	{
		if (exec_cmd->infile->fd_tmp != -1)
			close(exec_cmd->infile->fd_tmp);
		if (exec_cmd->outfile->fd_tmp != -1)
			close(exec_cmd->infile->fd_tmp);
		return (1);
	}
	// teste = fork();
	// if (teste == 0)
	exec(exec_cmd, hash_env);
	// else
	// 	waitpid(teste);
	return (0);
}

int	ft_sizeseg(t_segment *segment)
{
	int	i;

	i = 0;
	while (segment)
	{
		i++;
		segment = segment->next;
	}
	return (i);
}

t_exec	*build_exec(t_ast *ast)
{
	t_exec		*new_exec;
	t_segment	*aux;
	int			i;

	i = 0;
	new_exec = ft_gc_calloc_root(1, sizeof(t_exec), "exec");
	if (!new_exec)
		return (NULL);
	new_exec->infile = ft_gc_calloc_root(1, sizeof(t_redirect), "exec");
	new_exec->outfile = ft_gc_calloc_root(1, sizeof(t_redirect), "exec");
	aux = ast->args->seg_lst->next;
	new_exec->args = ft_gc_calloc_root(ft_sizeseg(aux) + 1, sizeof(char *),
			"exec");
	if (!new_exec->args || !new_exec->infile || !new_exec->outfile)
		return (NULL);
	while (aux)
	{
		new_exec->args[i++] = aux->text;
		aux = aux->next;
	}
	new_exec->infile->fd_tmp = -1;
	new_exec->outfile->fd_tmp = -1;
	return (new_exec);
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
