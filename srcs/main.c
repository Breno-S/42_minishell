/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:21:07 by brensant          #+#    #+#             */
/*   Updated: 2025/12/18 00:19:49 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "parsesh.h"
#include "types.h"

int		save_files(struct dirent *ent, int type, t_list **head);
t_list	*all_files(int type);

int	main(int argc, char *argv[], char *envp[])
{
	t_hash_env	**hash_env;
	t_list		*files;

	ft_gc_init();
	hash_env = (t_hash_env **)create_hash_env(envp, argv);
	files = all_files(OCULT);
	while (files)
	{
		printf("\n %d %s \n", argc, (char *)files->content);
		files = files->next;
	}
	// rl_clear_history();
	ft_gc_end();
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
