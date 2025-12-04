/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:55:48 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/03 18:59:03 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "libft.h"

int	main(int argc, char **argv, char **envp)
{
	char	**teste;
	char	**teste_2;

	// t_msh *msh;
	ft_gc_init();
	// msh = ft_gc_calloc_root(1, sizeof(msh), "main_data");
	// msh->envp = envp;
	// msh->ret = ft_main_loop(msh);
	// argv = NULL;
	// argc = 0;
	if (export_env(envp))
		return (1);
	ft_printf("%d %s\n", argc, argv[0]);
	teste = ft_trim_env(envp[20], '=');
	ft_printf("%s %s \n", teste[0], teste[1]);
	ft_export((const char *)"PATH=HAHAHAHAHAHAH", 0);
	ft_export((const char *)"ARROZ=FEIJAO", 0);
	ft_export(NULL, 0);
	// ft_env(0);
	ft_printf("\n\n\n\n\n");
	teste_2 = create_envp_arg(ft_gc_call_root("env")->lst->head);
	ft_printf("%s \n\n\n\n\n\n\n\n\n", teste_2[0]);
	ft_printf("\n\n\n\n\n");
	ft_unset("PATH");
	ft_env(0);
	ft_gc_end();
}
