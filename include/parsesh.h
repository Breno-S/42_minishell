/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsesh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:22:36 by brensant          #+#    #+#             */
/*   Updated: 2025/12/04 15:59:31 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSESH_H
# define PARSESH_H

# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "types.h"

// LEXER

t_lexer		lexer_new(const char *content, size_t content_len);
int			lexer_starts_with(t_lexer *l, const char *prefix);
void		lexer_chop_char(t_lexer *l, size_t len);
t_token		*lexer_next(t_lexer *l);
t_token		*lexer_token_list(t_lexer *l);

// LEXER UTILS

void		lexer_trim_left(t_lexer *l);
int			is_metachar(char c);

// LEXER AUX

void		handle_metachar(t_lexer *l, t_token **t);
void		handle_word(t_lexer *l, t_token **t);

// TOKEN

t_token		*token(t_token_class class, const char *text, size_t text_len);
// t_token		*token_word(t_lexer *l, const char *text, size_t text_len);
const char	*token_class_name(t_token_class class);
void		token_add(t_token **token_list, t_token *new);

// SEGMENT

t_segment	*segment(t_seg_type type, const char *text, size_t text_len);
void		segment_add(t_token_word *t, t_segment *new);

#endif //PARSESH_H
