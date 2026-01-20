/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:38:55 by brensant          #+#    #+#             */
/*   Updated: 2026/01/20 16:56:22 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "includes.h"

# define PROMPT "brensant&rgomes-d:Madshell> "

typedef enum e_error_type
{
	ERR_DEFAULT,
	ERR_SYNTAX,
	ERR_CMD_NOT_FOUND,
	ERR_FILE_NOT_FOUND,
	ERR_PERMISSION,
	ERR_IS_DIR,
	ERR_AMBIG_REDIR,
}						t_error_type;

typedef enum e_token_class
{
	TOKEN_END,
	TOKEN_INVALID,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_OPEN_PAREN,
	TOKEN_CLOSE_PAREN,
	TOKEN_COMMENT,
	TOKEN_REDIR_INPUT,
	TOKEN_REDIR_OUTPUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_NEWLINE,
}						t_token_class;

typedef enum e_seg_type
{
	OUTSIDE,
	DQUOTES,
	SQUOTES,
	VAR_FIXED,
	CMD_FIXED,
	LITERAL,
	VAR_SPLIT,
	CMD_SPLIT,
	WILDCARD,
}						t_seg_type;

typedef struct s_segment
{
	t_seg_type			type;
	char				*text;
	struct s_segment	*next;
}						t_segment;

typedef struct s_token_word
{
	t_token_class		class;
	const char			*text;
	size_t				text_len;
	struct s_token		*next;
	t_segment			*seg_lst;
}						t_token_word;

typedef struct s_token
{
	t_token_class		class;
	const char			*text;
	size_t				text_len;
	struct s_token		*next;
}						t_token;

typedef struct s_lexer
{
	const char			*str;
	size_t				str_len;
	size_t				idx;
	int					dquote_flag;
	int					squote_flag;
	int					cmd_lvl;
}						t_lexer;

typedef struct s_parser
{
	t_token				*tokens;
	t_token				*idx;
	int					paren_flag;
}						t_parser;

typedef enum e_node_type
{
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_CMD,
	NODE_SUB,
	NODE_CMD_BUILTIN,
}						t_node_type;

typedef struct s_io_node
{
	t_token_class		type;
	t_token_word		*io_target;
	struct s_io_node	*next;
	int					is_quoted_here;
}						t_io_node;

typedef struct s_pids
{
	pid_t				*pids;
	int					total;
	t_node_type			type_head;
}						t_pids;

typedef struct s_exec
{
	int					infile;
	int					outfile;
	char				*cmd;
	char				**args;
	int					error;
	int					pipefd[2];
}						t_exec;

typedef struct s_heredoc
{
	int					fd_tmp;
	char				*path;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_ast
{
	t_node_type			type;
	struct s_ast		*left;
	struct s_ast		*right;
	t_token_word		*args;
	t_io_node			*redirs;
	t_exec				*cmd;
	int					chan_com;
	int					is_head;
	t_pids				*pids;
	t_heredoc			*heredoc;

}						t_ast;

// EXEC STRUCTS

typedef enum e_env_type
{
	T_ENV,
	T_SET,
	T_INTERNAL,
	T_EXEC
}						t_env_type;

typedef struct s_hash_env
{
	char				*content;
	int					type_var;
	int					has_content;
	struct s_hash_env	*next;
}						t_hash_env;

typedef struct s_msh
{
	t_hash_env			**hash_env;
	char				**envp;
	t_token				*token_list;
	t_ast				*ast;
	char				*line;
	struct termios		term_settings;
}						t_msh;

#endif /* TYPES_H */
