/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 18:14:06 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/15 19:28:33 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	ft_exit(t_msh *aux_exec)
{
	finish_tree(aux_exec, 0);
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 2);
	exit(0);
}

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
