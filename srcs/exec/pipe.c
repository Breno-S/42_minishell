/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:17:04 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/14 16:41:29 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	pipe_exec(t_ast *ast, t_aux_exec *aux_exec, t_pids **pids)
{
	int	rtn;

	rtn = 1;
	if (!open_pipeline(&ast->left->cmd))
		ast->right->chan_com = ast->left->cmd->pipefd[0];
	else
		ast->left->cmd->error = 1;
	if (ast->left->cmd->outfile == -1 && ast->left->cmd->pipefd[0] > 0)
		ast->left->cmd->outfile = ast->left->cmd->pipefd[1];
	if (ast->chan_com > 0)
		ast->left->chan_com = ast->chan_com;
	ast->chan_com = 0;
	if (ast->left->cmd->outfile != -1)
		verify_sigpipe(ast);
	rtn = exec_tree(ast->left, aux_exec, pids);
	rtn = exec_tree(ast->right, aux_exec, pids);
	return (rtn);
}

int	open_pipeline(t_exec **cmd)
{
	if (pipe(cmd[0]->pipefd) == -1)
	{
		perror("Minishell");
		return (1);
	}
	return (0);
}

void	verify_sigpipe(t_ast *ast)
{
	if (ast->left->type == NODE_CMD_BUILTIN)
	{
		if (ast->right->type == NODE_CMD
			|| ast->right->type == NODE_CMD_BUILTIN)
		{
			if (ast->right->cmd->infile != -1)
				ast->left->cmd->error = 1;
		}
		else if (ast->right->type == NODE_PIPE)
		{
			if (ast->right->left->cmd->infile != -1)
				ast->left->cmd->error = 1;
		}
	}
}
