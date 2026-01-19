/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:17:04 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/19 13:19:10 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "parsesh.h"

int	pipe_exec(t_ast *ast, t_msh *aux_exec, t_pids **pids)
{
	int	rtn;

	rtn = 1;
	if (!ast->left->cmd)
		if (expand_atom(ast->left))
			return (rtn);
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
		perror("\033[0;31mMinishell");
		ft_putstr_fd("\033[0m", 2);
		return (1);
	}
	return (0);
}

void	verify_sigpipe(t_ast *ast)
{
	t_io_node *aux;

	aux = NULL;
	if (ast->left->type == NODE_CMD_BUILTIN)
	{
		if (ast->right->type == NODE_CMD
			|| ast->right->type == NODE_CMD_BUILTIN)
			aux = ast->right->redirs;
		else if (ast->right->type == NODE_PIPE)
				aux = ast->right->left->redirs;
	}
	while (aux)
	{
		if (aux->type == TOKEN_REDIR_HEREDOC
				|| aux->type == TOKEN_REDIR_INPUT)
		{
			ast->left->cmd->error = 1;
			break ;
		}
		aux = aux->next;
	}
}
