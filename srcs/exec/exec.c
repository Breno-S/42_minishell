/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:33:11 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/11 00:06:23 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	exec_tree(t_ast *ast, t_aux_exec *exec, t_pids **pids)
{
	int		rtn;
	t_pids	*my_pid;

	rtn = 1;
	my_pid = create_pids_list(&ast, pids);
	if (!my_pid)
		return (1);
	pids = &my_pid;
	if (ast->type == NODE_CMD)
		rtn = handle_cmd(ast, exec, pids);
	else if (ast->type == NODE_CMD_BUILTIN)
		rtn = handle_builtin(ast, exec, pids);
	else if (ast->type == NODE_AND)
		rtn = exec_and(ast, exec);
	else if (ast->type == NODE_OR)
		rtn = exec_or(ast, exec);
	else if (ast->type == NODE_PIPE)
		rtn = pipe_exec(ast, exec, pids);
	// else if (ast->type == NODE_SUB)
	// 	rtn = sub_exec(ast, exec, pids);
	if (ast->is_head)
		rtn = wait_childs(ast, pids[0], rtn);
	return (rtn);
}

t_pids	*create_pids_list(t_ast **ast, t_pids **pids)
{
	t_pids	*my_pids;

	if (!pids && ast[0]->is_head == 0)
	{
		ast[0]->is_head = 1;
		my_pids = ft_gc_calloc_root(1, sizeof(t_pids), "temp");
		if (!my_pids)
		{
			perror("Minishell");
			return (NULL);
		}
		my_pids->type_head = ast[0]->type;
		ast[0]->pids = my_pids;
		return (my_pids);
	}
	return (pids[0]);
}

int	wait_childs(t_ast *ast, t_pids *pids, int rtn_sys)
{
	int	i;
	int	rtn;

	i = 0;
	rtn = 1;
	while (i < pids->total)
		waitpid((pid_t)pids->pids[i++], &rtn, 0);
	if (ast->type == NODE_AND || ast->type == NODE_OR
		|| ast->type == NODE_CMD_BUILTIN)
		return (rtn_sys);
	return (WEXITSTATUS(rtn));
}
