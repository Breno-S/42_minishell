/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:55:48 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/01 19:12:20 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "libft.h"

int	main(int argc, char **argv, char **envp)
{
	// t_msh *msh;
	char **teste;
	ft_gc_init();
	// msh = ft_gc_calloc_root(1, sizeof(msh), "main_data");
	// msh->envp = envp;
	// msh->ret = ft_main_loop(msh);
	argv = NULL;
	argc = 0;
	teste = ft_trim_env(envp[20], '=');
	ft_printf("%s %s \n",teste[0], teste[1]);
	ft_gc_end();
}
