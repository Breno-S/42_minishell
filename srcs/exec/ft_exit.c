/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 18:14:06 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/20 13:50:35 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

static long long	ft_sizemult(long long n);
static long long	check_out_of_bounds(char *args, long long rtn);

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
	int			i;
	long long	rtn;

	i = 0;
	rtn = 0;
	while (ft_isspace(args[i]))
		i++;
	if (args[i] == '-' || args[i] == '+')
		i++;
	while (args[i] == 48)
		i++;
	rtn = ft_atoll(args);
	if (check_out_of_bounds(&args[i], rtn) == rtn)
	{
		while (args[i])
		{
			if (!ft_isdigit(args[i++]))
				rtn = print_exit_error(2, args);
			if (!ft_isdigit(args[i++]))
				break ;
		}
	}
	else
		rtn = print_exit_error(2, args);
	return (rtn);
}

static long long	check_out_of_bounds(char *args, long long rtn)
{
	long long	rtn_verify;
	long long	len_nbr;
	int			i;

	i = 0;
	rtn_verify = rtn;
	len_nbr = ft_sizemult(rtn_verify);
	while (args[i])
	{
		if (rtn_verify >= 0 && (!((rtn_verify / len_nbr) + '0' == args[i++])))
			return (2);
		else if (rtn_verify < 0 && (!(((rtn_verify / len_nbr) * -1)
					+ '0' == args[i++])))
			return (2);
		rtn_verify = rtn % len_nbr;
		len_nbr = len_nbr / 10;
	}
	return (rtn);
}

static long long	ft_sizemult(long long n)
{
	long long	qt_char;
	long long	verify;

	verify = 1;
	qt_char = 0;
	while (n >= 10 || n <= -10)
	{
		qt_char++;
		n /= 10;
	}
	qt_char += 1;
	while (qt_char-- > 1)
		verify *= 10;
	return (verify);
}

int	print_exit_error(int type, char *str)
{
	if (type == 1)
		ft_putendl_fd("\033[0;31mMinishell: exit: too many arguments\033[0m",
			2);
	else if (type == 2)
	{
		ft_putstr_fd("\033[0;31mMinishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": numeric argument required\033[0m", 2);
		return (2);
	}
	return (1);
}
