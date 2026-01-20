/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:21:17 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/20 16:26:39 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signalsh.h"

void	handler_interactive(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

int	check_signal_state(void)
{
	if (g_signal == SIGINT)
	{
		rl_done = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return (0);
}

void	set_signal_interactive(void)
{
	struct sigaction	sa;

	sa = (struct sigaction){0};
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &handler_interactive;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_signal_fork(pid_t pid)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (!pid)
	{
		sa.sa_handler = SIG_DFL;
		sigaction(SIGQUIT, &sa, NULL);
		sigaction(SIGINT, &sa, NULL);
	}
	if (pid)
	{
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
		sigaction(SIGINT, &sa, NULL);
	}
}
