/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execsh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:10:33 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/16 13:10:03 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECSH_H
# define EXECSH_H

# include "types.h"

// MAIN LOOP

int			ft_main_loop(t_msh *msh);

// UTILS ENV

void		**create_hash_env(char **arr);
int			count_hash(char *var);
char		**create_envp_arg(t_list *env);
char		**ft_trim_env(char *envp, char sep, char *categ);

// ENV

int			ft_env(void **hash_env, int fd);

// EXPORT

int			ft_export(t_hash_env **hash_table, const char *var, int fd);
int			ft_remove_var(void *content, t_ext_list *root);
int			change_env(int hash, t_hash_env **hash_table, char **str);


int			ft_print_export(t_hash_env **hash_table, int fd);
int			aux_print_export(t_hash_env **hash_table, char ***envs);
int			sort_print(char **envs);
int			ft_fix_print(char *env, int fd);

// HANDLE HASH

void		ft_hashadd_back(t_hash_env **lst, t_hash_env *new);
t_hash_env	*ft_hashnew(void *content, int type);
int			hashpop(t_hash_env **head, t_hash_env *rm_hash);

// UNSET

int			ft_unset(t_hash_env **hash_table, const char *var);

// EXPAND

char		*var_exp(char *var_name);
t_redirect	*create_heredoc(char *eof);

// GLOB

int			aux_exp_glob(DIR **dir, char ***files);
char		**exp_glob(void);

// PWD
// char		*pwd(int fd);

#endif // EXECSH_H
