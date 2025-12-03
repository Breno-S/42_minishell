/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:55:48 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/03 18:08:13 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"
#include "execsh.h"
#include "types.h"

//    ls -la > outfile && echo -n hello

int	main(void)
{
	t_lexer		l;
	t_token		*t;
	char		*line;

	ft_gc_init();
	while (1)
	{
		line = ft_gcfct_register(readline("Madshell> "), GC_DATA)->content;
		if (!line)
			break;
		add_history(line);
		l = lexer_new(line, ft_strlen(line));
		t = lexer_next(&l);
		while (t->class != TOKEN_END)
		{
			printf("%.*s (%s)\n", t->text_len, t->text, token_class_name(t->class));
			t = lexer_next(&l);
		}
		ft_gc_del_root("temp");
		ft_gc_collect();
	}
	rl_clear_history();
	ft_gc_end();
}
