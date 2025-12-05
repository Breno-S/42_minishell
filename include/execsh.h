/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execsh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:10:33 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/05 14:30:56 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECSH_H
# define EXECSH_H

# include "libft.h"
# include "types.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>

typedef enum e_env_type
{
	T_ENV,
	T_SET,
}						t_env_type;

typedef struct s_hash_env
{
	char				*content;
	int					type_var;
	int					has_content;
	struct s_hash_env	*next;
}						t_hash_env;

int						ft_main_loop(t_msh *msh);
char					**ft_trim_env(char *envp, char sep);
void					ft_hashadd_back(t_hash_env **lst, t_hash_env *new);
void					**create_hash_env(char **arr);
int						count_hash(char *var);
t_hash_env				*ft_hashnew(void *content, int type);

int						ft_export(t_hash_env **hash_table, const char *var,
							int fd);
int						export_env(char **arr);
int						ft_env(void **hash_env, int fd);
int						ft_unset(const char *var);
char					**create_envp_arg(t_list *env);

#endif // EXECSH_H
