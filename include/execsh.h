/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execsh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:10:33 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/17 10:12:08 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECSH_H
# define EXECSH_H

# include "types.h"

// UTILS ENV

t_hash_env	**create_hash_env(char **arr, char **argv);
int			count_hash(const char *var);
char		**create_envp_arg(t_list *env);
char		**ft_trim_env(char *envp, char sep, char *categ);

// ENV

int			ft_env(t_hash_env **hash_env, int fd);

// EXPORT

int			ft_export(t_exec *exec, t_hash_env **hash_table, int fd);
int			ft_remove_var(void *content, t_ext_list *root);
int			change_env(int hash, t_hash_env **hash_table, char **str);
int			modify_var(char *str, int hash, t_hash_env **hash_table);
int			verify_valid_var(char *var);

void		export_error(char *str);
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
int			import_special_args(t_hash_env **hash_env);

int			save_return(int rtn, t_hash_env **hash_table);

// UNSET

int			ft_unset(t_exec *cmd, t_hash_env **hash_table);
t_hash_env	*aux_unset(t_hash_env **hash_table, const char *var);
int			remove_env_root(void *arg, t_list *head);

// EXPAND

char		*var_exp(const char *var_name);

// HEREDOC

t_heredoc	*create_heredoc(char *eof);
char		*access_temp_file(int tmp);
void		print_warning(char *eof, int count);
int			loop_heredoc(char *eof, t_heredoc *heredoc);
int			handle_heredoc(t_ast *ast);

int			open_heredoc_tree(t_ast *ast);
int			expand_heredoc(t_heredoc *heredoc);
int			verify_text(char *str, t_heredoc *heredoc);
int			exp_heredoc(char *str, int fd_hr);
void		fix_list_heredoc(t_ast *ast, t_heredoc *heredoc);

// PWD

int			ft_pwd(int fd);
int			aux_pwd(char **str);

// CD

int			ft_cd(t_exec *exec, t_hash_env **env);
int			cd_exec(char *new_path, t_hash_env **env);
int			cd_special(t_hash_env **env, int type);
int			update_pwd(int type, t_hash_env **hash_table);
int			cd_error(char *arg, int type);

// ECHO

int			ft_echo(t_exec *cmd, int fd);
int			verify_option(char **args);

// GLOB

char		*glob_exp(t_token *token_o);
int			save_files(struct dirent *ent, int type, t_list **head,
				t_segment *seg_lst);
t_list		*all_files(int type, t_segment *seg_lst);
int			match_pattern(t_segment *seg_lst, char *content,
				t_segment *head_seg);
int			check_literal_match(t_segment *aux_seg, char *content,
				unsigned long i);

// EXIT

int			ft_exit(t_exec *exec, t_msh *aux_exec);
int			print_exit_error(int type, char *str);
int			verify_exit_arg(char *args);

// EXEC BUILTIN

int			exec_builtin(t_exec *exec, t_msh *aux_exec);
int			handle_builtin(t_ast *ast, t_msh *exec, t_pids **pids);
int			list_builtin(t_exec *exec, t_msh *aux_exec);
int			fork_builtin(t_exec *cmd, t_msh *aux_exec, t_pids **pids,
				int chan_com);

// BUILD CMD

t_exec		*build_cmd(t_ast *ast);
int			ft_sizeseg(t_token_word *args);

t_exec		*build_exec(t_ast *ast);
int			build_aux_exec(t_msh *msh);
int			copy_args(t_token_word *args, t_exec **cmd);
char		**find_path(void);
char		*find_executable(char *arg, char **path, t_exec **exec);
char		*handle_search(char *arg, t_exec **exec);
void		print_error_find(int type, char *arg, t_exec **exec);
int			verify_file(char *file);

// EXEC

int			exec_tree(t_ast *ast, t_msh *msh, t_pids **pids);
t_pids		**create_pids_list(t_ast **ast, t_pids **pids);
int			wait_childs(t_ast *ast, t_pids *pids, int rtn_sys);
void		handle_error_msg_wait(int code);

int			exec(t_exec *exec, t_msh *aux_exec, int chan_com);
int			fork_exec(t_exec *cmd, t_msh *aux_exec, t_pids **pids,
				int chan_com);
int			is_builtins(char *cmd);
int			handle_cmd(t_ast *ast, t_msh *aux_exec, t_pids **pids);
int			dup_fds(t_exec *exec);

int			exec_and(t_ast *ast, t_msh *aux_exec);

int			exec_or(t_ast *ast, t_msh *aux_exec);

// CLEAN TREE

void		close_fd_parent(t_exec *cmd, int chan_com);

void		finish_tree(t_msh *aux_exec, int rtn);
void		close_fds_tree(t_ast *ast);
void		close_heredoc(t_ast *ast);

// REDIRS

int			handle_redirects(t_io_node *redirs, t_exec **exec, t_ast *ast);
int			open_infile(char *infile, t_exec **exec);
int			open_outfile(char *outfile, t_exec **exec, int type);
int			open_heredoc(t_exec **exec, t_ast *ast, int is_quoted_here);

// PIPE
int			pipe_exec(t_ast *ast, t_msh *aux_exec, t_pids **pids);
int			open_pipeline(t_exec **cmd);
void		verify_sigpipe(t_ast *ast);

// SGUBSHELL

int			sub_fork(t_ast *ast, t_msh *exec, t_pids **pids);
int			sub_exec(t_ast *ast, t_msh *exec);
t_exec		*build_sub(t_ast *ast);
void		dup_sub(t_ast *ast);

void		close_fds_tree_cmd(t_ast *ast);

#endif // EXECSH_H
