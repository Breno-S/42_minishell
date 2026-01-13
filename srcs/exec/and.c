/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:43:34 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/13 17:44:01 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	exec_and(t_ast *ast, t_aux_exec *aux_exec)
{
	int	rtn;

	rtn = 1;
	rtn = exec_tree(ast->left, aux_exec, NULL);
	if (rtn)
	{
		close_fds_tree(ast->right);
		return (rtn);
	}
	rtn = exec_tree(ast->right, aux_exec, NULL);
	return (rtn);
}
