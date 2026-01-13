/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:00:07 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/13 14:41:58 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

t_exec	*build_cmd(t_ast *ast)
{
	t_exec	*exec_cmd;

	exec_cmd = build_exec(ast);
	if (!exec_cmd)
		return (NULL);
	if (ast->redirs && handle_redirects(ast->redirs, &exec_cmd, ast))
		return (NULL);
	if (!is_builtins(exec_cmd->args[0]))
	{
		ast->type = NODE_CMD_BUILTIN;
		return (exec_cmd);
	}
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

	new_exec = ft_gc_calloc_root(1, sizeof(t_exec), "exec");
	if (!new_exec)
		return (NULL);
	aux = ast->args;
	new_exec->args = ft_gc_calloc_root(ft_sizeseg(aux) + 1, sizeof(char *),
			"exec");
	if (!new_exec->args)
		return (NULL);
	copy_args(aux, &new_exec);
	new_exec->infile = -1;
	new_exec->outfile = -1;
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

t_aux_exec	*build_aux_exec(t_ast *ast, t_hash_env **hash_table)
{
	char		**new_envp;
	t_aux_exec	*aux_exec;

	if (aux_print_export(hash_table, &new_envp))
	{
		perror("Minishell");
		return (NULL);
	}
	ft_gcfct_register((void *)new_envp, GC_DATA);
	aux_exec = ft_gc_calloc_root(1, sizeof(t_aux_exec), "temp");
	if (!aux_exec)
	{
		perror("Minishell");
		return (NULL);
	}
	aux_exec->envp = new_envp;
	aux_exec->hash_env = hash_table;
	aux_exec->head = ast;
	return (aux_exec);
}
