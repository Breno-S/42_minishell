/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 18:14:06 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/16 21:27:20 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	ft_exit(t_exec *exec, t_msh *aux_exec)
{
	long long	rtn;
	int			i;

	i = 0;
	rtn = 0;
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 2);
	while (exec->args[i])
		i++;
	if (i > 2)
		return (print_exit_error(1, NULL));
	if (exec->args[1])
		rtn = verify_exit_arg(exec->args[1]);
	finish_tree(aux_exec, 0);
	exit((unsigned char)rtn);
}

int	verify_exit_arg(char *args)
{
	int	i;
	int	rtn;

	i = 0;
	rtn = 0;
	while (ft_isspace(args[i]))
		i++;
	if (args[i] == '-' || args[i] == '+')
		i++;
	rtn = ft_atoll(args);
	while (args[i])
	{
		if (!ft_isdigit(args[i++]))
		{
			rtn = print_exit_error(2, args);
			break ;
		}
	}
	return (rtn);
}

int	print_exit_error(int type, char *str)
{
	if (type == 1)
		ft_putendl_fd("Minishell: exit: too many arguments", 2);
	else if (type == 2)
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (2);
	}
	return (1);
}
