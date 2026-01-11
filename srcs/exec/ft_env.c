/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 23:10:32 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/10 23:26:59 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	ft_env(t_hash_env **hash_env, int fd)
{
	int			i;
	t_hash_env	*var;

	if (!hash_env)
		return (-1);
	i = 0;
	while (i < 256)
	{
		var = hash_env[i++];
		while (var)
		{
			if (var->type_var == T_ENV && var->has_content)
				ft_putendl_fd(var->content, fd);
			var = var->next;
		}
	}
	ft_putendl_fd("_=/usr/bin/env", fd);
	return (0);
}
