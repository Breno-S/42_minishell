/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 23:10:32 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/02 23:13:04 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execsh.h>

int ft_env(int fd)
{
	t_list	*env;

	env = ft_gc_call_root("env")->lst->head;
	while(env)
	{
		ft_putendl_fd(ft_to_gc_list(env->content)->content,fd);
		env = env->next;
	}
	return (0);
}
