/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:43:51 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/09 21:02:46 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	exec_or(t_ast *ast, char **envp)
{
	int	rtn;

	rtn = 1;
	rtn = exec_tree(ast->left, envp, NULL);
	if (!rtn)
		return (rtn);
	rtn = exec_tree(ast->right, envp, NULL);
	return (rtn);
}
