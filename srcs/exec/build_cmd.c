/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:00:07 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/19 13:27:37 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

t_exec	*build_cmd(t_ast *ast)
{
	t_exec	*exec_cmd;

	exec_cmd = build_exec(ast);
	if (!exec_cmd)
	{
		exec_cmd->error = 1;
		return (NULL);
	}
	if (ast->redirs && handle_redirects(ast->redirs, &exec_cmd, ast))
	{
		ast->cmd = exec_cmd;
		close_fds_tree_cmd(ast);
		exec_cmd->error = 1;
		return (exec_cmd);
	}
	if (ast->args && !is_builtins(exec_cmd->args[0]))
		ast->type = NODE_CMD_BUILTIN;
	return (exec_cmd);
}

int	ft_sizeseg(t_token_word *args)
{
	int	i;

	i = 0;
	while (args)
	{
		if (args->class != TOKEN_NEWLINE)
			i++;
		args = (t_token_word *)args->next;
	}
	return (i);
}

t_exec	*build_exec(t_ast *ast)
{
	t_exec			*new_exec;
	t_token_word	*aux;

	new_exec = ft_gc_calloc_root(1, sizeof(t_exec), "temp");
	new_exec->infile = -1;
	new_exec->outfile = -1;
	if (!new_exec)
		return (NULL);
	aux = ast->args;
	new_exec->args = ft_gc_calloc_root(ft_sizeseg(aux) + 1, sizeof(char *),
			"temp");
	if (copy_args(aux, &new_exec))
	{
		perror("\033[0;31mMinishell");
		ft_putstr_fd("\033[0m", 2);
		new_exec->error = 1;
	}
	return (new_exec);
}

int	copy_args(t_token_word *args, t_exec **cmd)
{
	int			i;
	t_segment	*aux;
	char		*arg_join;

	i = 0;
	while (args)
	{
		if (args->class != TOKEN_NEWLINE)
			aux = args->seg_lst;
		arg_join = ft_gc_calloc_root(1, 1, "temp");
		while (args->class != TOKEN_NEWLINE && aux)
		{
			if (aux->text)
				arg_join = ft_gcfct_register_root(ft_strjoin(arg_join,
							aux->text), "temp");
			if (!arg_join)
				return (1);
			aux = aux->next;
		}
		if (args->class != TOKEN_NEWLINE)
			cmd[0]->args[i++] = arg_join;
		args = (t_token_word *)args->next;
	}
	return (0);
}

int	build_aux_exec(t_msh *msh)
{
	char	**new_envp;

	if (aux_print_export(msh->hash_env, &new_envp))
	{
		perror("\033[0;31mMinishell");
		ft_putstr_fd("\033[0m", 2);
		return (1);
	}
	ft_gcfct_register(new_envp, GC_DATA);
	msh->envp = new_envp;
	return (0);
}
