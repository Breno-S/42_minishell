/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:33:11 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/05 20:47:19 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	handle_pre_exec(t_ast *ast)
{
	t_exec	*exec_cmd;
	int		i;

	i = 0;
	exec_cmd = build_exec(ast);
	if (!exec_cmd)
		return (1);
	exec_cmd->cmd = handle_search(ast->args->seg_lst->text);
	if (!exec_cmd->cmd)
		return (1);
	if (ast->redirs)
		handle_redirects(ast->redirs, &exec_cmd);
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

// int	exec(t_fork info, char *argv, char **path, char **envp)
// {
// 	char	*exec_path;
// 	char	**newargv;

// 	newargv = ft_gcfct_arr_register_root((void **)ft_split(argv, ' '), GC_DATA,
// 			"split");
// 	exec_path = find_executable(newargv[0], path);
// 	if (!exec_path || info.old_stdout == -1)
// 		close_fds(info, ALL);
// 	if (!exec_path || info.old_stdout == -1)
// 		control_gc(127);
// 	if (dup2(info.old_stdout, STDIN_FILENO) == -1)
// 		perror("dup2");
// 	if (info.index == info.argc)
// 	{
// 		if (dup2(info.fd[OUTFILE], STDOUT_FILENO) == -1)
// 			perror("dup2");
// 	}
// 	else if (dup2(info.pipefd[1], STDOUT_FILENO) == -1)
// 		perror("dup2");
// 	close_fds(info, CHILD);
// 	execve(exec_path, newargv, envp);
// 	perror("execve");
// 	control_gc(1);
// 	return (1);
// }
