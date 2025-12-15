/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:54:30 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/11 20:35:07 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//  struct sigaction {
//                void (*sa_handler)(int);
//                void (*sa_sigaction)(int, siginfo_t *, void *);
//                sigset_t sa_mask;
//                int sa_flags;
//                vazio (*sa_restorer)(void);
//            };

void	print_oi(int);

int	main(void)
{
	struct sigaction	*act;

	act = calloc(1, sizeof(struct sigaction));
	act->sa_handler = &print_oi;
	act->sa_flags = SA_RESTART;
	
	
	sigaction(SIGINT, act, NULL);
	while (1)
	{
		;
	}
	return (0);
}

flag_current_status = 2;
lst1 -> lst2 ->lst3
process_child -> exit(1)
pid1    pid2    pid3
kill()

void	print_oi(int)
{
	printf("oi\n");
	return ;
}
