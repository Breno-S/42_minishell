/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execsh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:10:33 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/17 16:05:32 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECSH_H
# define EXECSH_H

# include "types.h"

// MAIN LOOP

int			ft_main_loop(t_msh *msh);

// UTILS ENV

t_hash_env	**create_hash_env(char **arr, char **argv);
int			count_hash(const char *var);
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

int			import_envp(char **arr, t_hash_env **hash_env);
int			import_argv(char **arr, t_hash_env **hash_env);

// UNSET

int			ft_unset(t_hash_env **hash_table, const char *var);

// EXPAND

char		*var_exp(const char *var_name);

// HEREDOC

t_redirect	*create_heredoc(char *eof);
char		*access_temp_file(int tmp);
void		print_warning(char *eof, int count);

// GLOB

int			aux_exp_glob(DIR **dir, char ***files);
char		**exp_glob(void);

// PWD
// char		*pwd(int fd);

#endif // EXECSH_H
