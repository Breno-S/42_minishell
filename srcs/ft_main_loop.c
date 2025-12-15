/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:14:29 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/09 19:04:47 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	ft_main_loop(t_msh *msh)
{
	while (1)
	{
		msh->cmd = readline("Minishell$ ");
		add_history(msh->cmd);
		free(msh->cmd);
	}
}
