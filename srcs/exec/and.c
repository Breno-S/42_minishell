/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:43:34 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/08 20:12:30 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int exec_and(t_ast *ast, char **envp, t_pids **pids)
{
	int	rtn;

	rtn = 1;
	rtn = exec_tree(ast->left, envp, NULL);
	if (rtn)
		return (rtn);
	rtn = exec_tree(ast->right, envp, NULL);
	return (rtn);
}
