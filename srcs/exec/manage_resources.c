/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_resources.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 21:26:10 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/16 21:27:25 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

void	finish_tree(t_msh *aux_exec, int rtn)
{
	if (aux_exec && aux_exec->ast)
		close_fds_tree(aux_exec->ast);
	rl_clear_history();
	ft_gc_end();
	if (rtn)
		exit(rtn);
}

void	close_fds_tree(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type != NODE_CMD && ast->type != NODE_CMD_BUILTIN)
	{
		close_fds_tree(ast->left);
		close_fds_tree(ast->right);
		if (ast->chan_com > 2)
			close(ast->chan_com);
		ast->chan_com = 0;
		return ;
	}
	close_fds_tree_cmd(ast);
}

void	close_fds_tree_cmd(t_ast *ast)
{
	if (ast->cmd)
	{
		if (ast->cmd->infile > 2)
			close(ast->cmd->infile);
		ast->cmd->infile = -1;
		if (ast->cmd->outfile > 2)
			close(ast->cmd->outfile);
		ast->cmd->outfile = -1;
		if (ast->chan_com > 2)
			close(ast->chan_com);
		if (ast->cmd->pipefd[1] > 2)
			close(ast->cmd->pipefd[1]);
		if (ast->cmd->pipefd[0] > 2)
			close(ast->cmd->pipefd[0]);
	}
	ast->chan_com = 0;
	if (ast->heredoc)
	{
		while (ast->heredoc)
		{
			close(ast->heredoc->fd_tmp);
			ast->heredoc = ast->heredoc->next;
		}
	}
}
