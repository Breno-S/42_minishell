/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:38:55 by brensant          #+#    #+#             */
/*   Updated: 2025/12/05 19:04:42 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "libft.h"

typedef struct s_msh
{
	char		**envp;
	char	*tree;
	char		*childs;
	char		*cmd;
	int			ret;
}	t_msh;

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
	UNQUOTED,
	DQUOTES,
	SQUOTES
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
	size_t			seg_count;
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
	const char	*content;
	size_t		content_len;
	size_t		cursor;
}	t_lexer;

#endif // TYPES_H
