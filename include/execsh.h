/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execsh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:10:33 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/08 21:50:30 by rgomes-d         ###   ########.fr       */
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

int			ft_main_loop(t_msh *msh);
char		**ft_trim_env(char *envp, char sep, char *categ);
void		ft_hashadd_back(t_hash_env **lst, t_hash_env *new);
void		**create_hash_env(char **arr);
int			count_hash(char *var);
t_hash_env	*ft_hashnew(void *content, int type);
char		*var_exp(char *var_name);
int			ft_print_export(t_hash_env **hash_table, int fd);
int			ft_export(t_hash_env **hash_table, const char *var, int fd);
int			ft_env(void **hash_env, int fd);

int			ft_unset(t_hash_env **hash_table, const char *var);
char		**create_envp_arg(t_list *env);

int			hashpop(t_hash_env **head, t_hash_env *rm_hash);
#endif // EXECSH_H
