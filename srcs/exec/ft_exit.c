/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 18:14:06 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/11 16:45:10 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	ft_exit(t_aux_exec *aux_exec)
{
	finish_tree(aux_exec, 0);
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 2);
	exit(0);
}

void	finish_tree(t_aux_exec *aux_exec, int rtn)
{
	if (aux_exec && aux_exec->head)
		close_fds_tree(aux_exec->head);
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
	if (ast->cmd->infile->fd_tmp > 2)
		close(ast->cmd->infile->fd_tmp);
	ast->cmd->infile->fd_tmp = -1;
	if (ast->cmd->outfile->fd_tmp > 2)
		close(ast->cmd->outfile->fd_tmp);
	ast->cmd->outfile->fd_tmp = -1;
	if (ast->chan_com > 2)
		close(ast->chan_com);
	if (ast->cmd->pipefd[1] > 2)
		close(ast->cmd->pipefd[1]);
	if (ast->cmd->pipefd[0] > 2)
		close(ast->cmd->pipefd[0]);
	ast->chan_com = 0;
}
