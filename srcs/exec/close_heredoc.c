/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:06:52 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/14 21:16:44 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

void	close_heredoc(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == NODE_CMD && ast->heredoc)
	{
		while (ast->heredoc)
		{
			close(ast->heredoc->fd_tmp);
			ast->heredoc = ast->heredoc->next;
		}
	}
	close_heredoc(ast->right);
	close_heredoc(ast->left);
}
