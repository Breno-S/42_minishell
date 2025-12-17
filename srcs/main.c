/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:21:07 by brensant          #+#    #+#             */
/*   Updated: 2025/12/17 16:15:09 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"
#include "execsh.h"
#include "types.h"

void	traverse_tree(t_ast *ast, int indent);

int	main(int argc, char *argv[], char *envp[])
{
	// t_hash_env **hash_env;

	// ft_gc_init();
	// hash_env = (t_hash_env **)create_hash_env(envp);

	// // rl_clear_history();
	// ft_gc_end();
}

// while (1)
// {
// 	line = ft_gcfct_register(readline("Madshell> "), GC_DATA)->content;
// 	if (!line)
// 		break ;
// 	add_history(line);
// 	l = lexer_new(line, ft_strlen(line));
// 	token_list = lexer_token_list(&l);
// 	expand(token_list);
// 	p = parser_new(token_list);
// 	ast = parser_parse(&p);
// 	ft_gc_del_root("temp");
// 	ft_gc_collect();
// }
