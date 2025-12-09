/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:55:48 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/08 21:47:56 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "libft.h"

int	main(int argc, char **argv, char **envp)
{
	void	**hash_env;
	int		i;
	char	*str;

	// char	**teste_2;
	i = 0;
	ft_gc_init();
	hash_env = create_hash_env(envp);
	if (!hash_env)
		return (1);
	ft_printf("%d %s\n", argc, argv[0]);
	// ft_printf("%s %d %d", ((t_hash_env *)hash_env[37])->content,
	// 	((t_hash_env *)hash_env[37])->has_content,
	// 	((t_hash_env *)hash_env[37])->type_var);
	ft_printf("\n\n\n\n\n");
	ft_env(hash_env, 0);
	ft_printf("aqui passou 1\n");
	ft_export((t_hash_env **)hash_env,"TESTE",0);
	ft_printf("aqui passou 2\n");
	ft_printf("\n\n\n\n\n %d %s",i , var_exp("USER"));
	str = var_exp("PATH");
	ft_printf("\n\n\n\n\n %s", str);
	str = var_exp("TESTE");
	ft_printf("\n\n\n\n\n %s\n", str);
	ft_env(hash_env, 0);
	ft_printf("\n\n\n\n\n %s\n", str);
	ft_unset((t_hash_env **)hash_env,"TESTE");
	ft_unset((t_hash_env **)hash_env,"PATH");
	ft_unset((t_hash_env **)hash_env,"LS_COLORS");
	ft_export((t_hash_env **)hash_env,NULL,0);
	// teste_2 = create_envp_arg(ft_gc_call_root("env")->lst->head);
	// ft_printf("%s \n\n\n\n\n\n\n\n\n", teste_2[0]);
	// ft_printf("\n\n\n\n\n");
	ft_gc_end();
}
