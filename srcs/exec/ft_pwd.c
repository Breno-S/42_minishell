/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:07:18 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/17 18:08:57 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	ft_pwd(int fd)
{
	char	*str;
	int		rtn;

	rtn = aux_pwd(&str);
	if (rtn)
	{
		perror("\033[0;31mMinishell");
		ft_putstr_fd("\033[0m", 2);
		return (rtn);
	}
	ft_putendl_fd(str, fd);
	return (0);
}

int	aux_pwd(char **str)
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
	str[0] = pwd;
	return (0);
}
