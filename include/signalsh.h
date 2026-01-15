/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalsh.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:43:57 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/14 21:16:44 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALSH_H
# define SIGNALSH_H

# include "includes.h"

extern int	g_signal;

void		handler_interactive(int sig);
void		set_signal_interactive(void);
void		handler_heredoc(int sig);
void		set_signal_heredoc(void);
void		set_signal_fork(pid_t pid);

#endif
