/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:38:55 by brensant          #+#    #+#             */
/*   Updated: 2025/12/03 14:54:02 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "libft.h"


typedef struct s_cmd_tree
{
	int i;
}	t_cmd_tree;

typedef struct s_child
{
	int i;
}	t_child;

typedef struct s_msh
{
	char		**envp;
	t_cmd_tree	*tree;
	t_child		*childs;
	char		*cmd;
	int			ret;
}	t_msh;

typedef enum e_token_class
{
	TOKEN_END,
	TOKEN_INVALID,
	TOKEN_WORD,
	TOKEN_SUBSHELL,
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
}	t_token_kind;

typedef struct s_token
{
	t_token_kind	kind;
	const char		*text;
	size_t			text_len;
}	t_token;

typedef struct s_lexer
{
	const char	*content;
	size_t		content_len;
	size_t		cursor;
}	t_lexer;

int			lexer_starts_with(t_lexer *l, const char *prefix);
void		lexer_trim_left(t_lexer *l);
t_lexer		lexer_new(const char *content, size_t content_len);
const char	*token_kind_name(t_token_kind kind);
t_token		lexer_next(t_lexer *l);

#endif // TYPES_H
