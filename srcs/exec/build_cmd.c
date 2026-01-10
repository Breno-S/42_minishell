/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:00:07 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/09 20:54:03 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

t_exec	*build_cmd(t_ast *ast)
{
	t_exec	*exec_cmd;
	int		i;

	i = 0;
	exec_cmd = build_exec(ast);
	if (!exec_cmd)
		return (NULL);
	if (ast->redirs && handle_redirects(ast->redirs, &exec_cmd))
		return (NULL);
	// if (!is_builtins(exec_cmd->args[0]))
	// {
	// 	ast->type = NODE_CMD_BUILTIN;
	// 	return (exec_cmd);
	// }
	exec_cmd->cmd = handle_search(ast->args->seg_lst->text, &exec_cmd);
	return (exec_cmd);
}

int	ft_sizeseg(t_token_word *args)
{
	int			i;
	t_segment	*aux;

	i = 0;
	while (args)
	{
		aux = args->seg_lst;
		while (aux)
		{
			i++;
			aux = aux->next;
		}
		args = (t_token_word *)args->next;
	}
	return (i);
}

t_exec	*build_exec(t_ast *ast)
{
	t_exec			*new_exec;
	t_token_word	*aux;
	int				i;

	i = 0;
	new_exec = ft_gc_calloc_root(1, sizeof(t_exec), "exec");
	if (!new_exec)
		return (NULL);
	new_exec->infile = ft_gc_calloc_root(1, sizeof(t_redirect), "exec");
	new_exec->outfile = ft_gc_calloc_root(1, sizeof(t_redirect), "exec");
	aux = ast->args;
	new_exec->args = ft_gc_calloc_root(ft_sizeseg(aux) + 1, sizeof(char *),
			"exec");
	if (!new_exec->args || !new_exec->infile || !new_exec->outfile)
		return (NULL);
	copy_args(aux, &new_exec);
	new_exec->infile->fd_tmp = -1;
	new_exec->outfile->fd_tmp = -1;
	return (new_exec);
}

void	copy_args(t_token_word *args, t_exec **cmd)
{
	int			i;
	t_segment	*aux;

	i = 0;
	while (args)
	{
		aux = args->seg_lst;
		while (aux)
		{
			cmd[0]->args[i++] = args->seg_lst->text;
			aux = aux->next;
		}
		args = (t_token_word *)args->next;
	}
	return ;
}
