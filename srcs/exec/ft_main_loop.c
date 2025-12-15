/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:14:29 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/15 18:58:46 by brensant         ###   ########.fr       */
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
