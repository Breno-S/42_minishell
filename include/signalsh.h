/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalsh.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:43:57 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/19 18:08:13 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALSH_H
# define SIGNALSH_H

# include "includes.h"

extern int	g_signal;

void	handler_interactive(int sig);
void	set_signal_interactive(void);
void	set_signal_fork(pid_t pid);
int		check_signal_state(void);
int		check_signal_state_heredoc(void);

#endif /* SIGNALSH_H */
