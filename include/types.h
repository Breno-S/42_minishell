/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:38:55 by brensant          #+#    #+#             */
/*   Updated: 2025/12/12 17:01:34 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "libft.h"

// typedef struct s_msh
// {
// 	char		**envp;
// 	t_cmd_tree	*tree;
// 	t_child		*childs;
// 	char		*cmd;
// 	int			ret;
// }	t_msh;

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
}	t_token_class;

typedef enum e_seg_type
{
	LITERAL,
	VAR_SPLIT,
	VAR_FIXED,
	CMD_SPLIT,
	CMD_FIXED,
	WILDCARD,
}	t_seg_type;

typedef struct s_segment
{
	t_seg_type			type;
	char				*text;
	struct s_segment	*next;
}	t_segment;

typedef struct s_token_word
{
	t_token_class	class;
	const char		*text;
	size_t			text_len;
	struct s_token	*next;
	t_segment		*seg_lst;
}	t_token_word;

typedef struct s_token
{
	t_token_class	class;
	const char		*text;
	size_t			text_len;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	const char	*str;
	size_t		str_len;
	size_t		idx;
	int			dquote_flag;
	int			squote_flag;
	int			cmd_lvl;
}	t_lexer;

typedef struct s_parser
{
	t_token	*tokens;
	t_token	*idx;
}	t_parser;

typedef enum e_node_type
{
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_CMD,
	NODE_SUB,
}	t_node_type;

typedef struct s_io_node
{
	t_token_class		type;
	t_token_word		*io_target;
	struct s_io_node	*next;
}	t_io_node;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	t_token_word	*args;
	t_io_node		*redirs;
}	t_ast;

#endif // TYPES_H
