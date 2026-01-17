/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:33:11 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/16 21:53:35 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "parsesh.h"
#include "signalsh.h"

int	exec_tree(t_ast *ast, t_msh *msh, t_pids **pids)
{
	int	rtn;

	rtn = 1;
	if (!pids && ast->type != NODE_AND && ast->type != NODE_OR)
		if (!traverse_expand(ast, msh->hash_env))
			return (1);
	pids = create_pids_list(&ast, pids);
	if (!pids)
		return (1);
	if (ast->type == NODE_CMD)
		rtn = handle_cmd(ast, msh, pids);
	else if (ast->type == NODE_CMD_BUILTIN)
		rtn = handle_builtin(ast, msh, pids);
	else if (ast->type == NODE_AND)
		rtn = exec_and(ast, msh);
	else if (ast->type == NODE_OR)
		rtn = exec_or(ast, msh);
	else if (ast->type == NODE_PIPE)
		rtn = pipe_exec(ast, msh, pids);
	else if (ast->type == NODE_SUB)
		rtn = sub_fork(ast, msh, pids);
	if (ast->is_head)
		rtn = wait_childs(ast, pids[0], rtn);
	return (rtn);
}

t_pids	**create_pids_list(t_ast **ast, t_pids **pids)
{
	t_pids	**my_pids;

	my_pids = ft_gc_calloc_root(1, sizeof(t_pids *), "temp");
	if (!my_pids)
	{
		perror("Minishell");
		return (NULL);
	}
	if (!pids && ast[0]->is_head == 0)
	{
		ast[0]->is_head = 1;
		my_pids[0] = ft_gc_calloc_root(1, sizeof(t_pids), "temp");
		if (!my_pids)
		{
			perror("Minishell");
			return (NULL);
		}
		my_pids[0]->type_head = ast[0]->type;
		ast[0]->pids = my_pids[0];
		return (my_pids);
	}
	return (pids);
}

int	wait_childs(t_ast *ast, t_pids *pids, int rtn_sys)
{
	int	i;
	int	rtn;

	i = 0;
	rtn = 1;
	while (i < pids->total)
	{
		waitpid((pid_t)pids->pids[i++], &rtn, 0);
		if (WIFSIGNALED(rtn))
		{
			if (!g_signal)
				handle_error_msg_wait(WTERMSIG(rtn));
			rtn = 128 + WTERMSIG(rtn);
		}
		else if (WIFEXITED(rtn))
			rtn = WEXITSTATUS(rtn);
	}
	if (ast->type == NODE_AND || ast->type == NODE_OR
		|| ast->type == NODE_CMD_BUILTIN)
		return (rtn_sys);
	return (rtn);
}

void	handle_error_msg_wait(int code)
{
	if (code == 11)
		ft_putendl_fd("Segmentation fault (core dumped)", 2);
	else if (code == 7)
		ft_putendl_fd("Bus error", 2);
	else if (code == 3)
		ft_putendl_fd("Quit (core dumped)", 2);
	else if (code == 6)
		ft_putendl_fd("Aborted", 2);
	else if (code == 8)
		ft_putendl_fd("Floating point exception", 2);
	else if (code == 2)
		ft_putendl_fd("", 2);
	g_signal = 128 + code;
}
