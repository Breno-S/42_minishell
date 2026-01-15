/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:43:51 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/15 19:01:44 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	exec_or(t_ast *ast, t_msh *aux_exec)
{
	int	rtn;

	rtn = 1;
	if (ast->chan_com > 2)
		ast->left->chan_com = ast->chan_com;
	ast->chan_com = 0;
	rtn = exec_tree(ast->left, aux_exec, NULL);
	if (!rtn)
	{
		close_fds_tree(ast->right);
		return (rtn);
	}
	rtn = exec_tree(ast->right, aux_exec, NULL);
	return (rtn);
}
