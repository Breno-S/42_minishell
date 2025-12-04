/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execsh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:10:33 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/04 13:53:16 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECSH_H
# define EXECSH_H

# include "libft.h"
# include "types.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_env_type
{
	T_ENV,
	T_SET,
}						t_env_type;

typedef struct s_hash_env
{
	char				*var;
	int					type_var;
	int					content;
	struct s_hash_env	*next;
}						t_hash_env;

int						ft_main_loop(t_msh *msh);
char					**ft_trim_env(char *envp, char sep);
int						ft_export(const char *var, int fd);
int						export_env(char **arr);
int						ft_env(int fd);
int						ft_unset(const char *var);
char					**create_envp_arg(t_list *env);

#endif // EXECSH_H
