/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:21:17 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/14 21:16:44 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signalsh.h"

void	handler_interactive(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_signal = 130;
}

void	set_signal_interactive(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler_interactive;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	handler_heredoc(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_signal = 130;
}

void	set_signal_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler_heredoc;
	sigaction(SIGINT, &sa, NULL);
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
