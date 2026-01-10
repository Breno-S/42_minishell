/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:07:18 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/09 15:16:51 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	ft_pwd(int fd)
{
	char	*pwd;
	int		mult;

	mult = 1;
	pwd = ft_gc_calloc(mult, 100, GC_DATA)->content;
	if (!pwd)
		return (1);
	while (1)
	{
		if (!getcwd(pwd, (mult * 100) - 1))
		{
			if (errno == 34)
			{
				pwd = ft_gc_calloc(++mult, 100, GC_DATA)->content;
				if (!pwd)
					return (1);
			}
			else
				return (errno);
		}
		else
			break ;
	}
	ft_putstr_fd(pwd, fd);
	return (0);
}
