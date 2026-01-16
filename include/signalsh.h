/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalsh.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:43:57 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/16 12:42:58 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALSH_H
# define SIGNALSH_H

# include "includes.h"

extern int	g_signal;

void		handler_interactive(int sig);
void		set_signal_interactive(void);
void		set_signal_fork(pid_t pid);
int			check_signal_state(void);
int			check_signal_state_heredoc(void);

#endif
