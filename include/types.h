/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:38:55 by brensant          #+#    #+#             */
/*   Updated: 2025/12/02 20:10:44 by brensant         ###   ########.fr       */
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
	TOKEN_STRING_SINGLE,
	TOKEN_STRING_DOUBLE,
	TOKEN_COMMENT,
	TOKEN_REDIR_INPUT,
	TOKEN_REDIR_OUTPUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_WILDCARD,
}	t_token_class;

typedef struct s_token
{
	t_token_class	class;
	const char		*text;
	size_t			text_len;
}	t_token;

typedef struct s_lexer
{
	const char	*content;
	size_t		content_len;
	size_t		cursor;
}	t_lexer;

#endif // TYPES_H
