/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsesh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:22:36 by brensant          #+#    #+#             */
/*   Updated: 2025/12/03 17:53:38 by brensant         ###   ########.fr       */
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
void		lexer_trim_left(t_lexer *l);
void		lexer_chop_char(t_lexer *l, size_t len);
t_token		*lexer_next(t_lexer *l);

// LEXER AUX

int		is_metachar(char c);
void	handle_metachar(t_lexer *l, t_token **t);
void	handle_word(t_lexer *l, t_token **t);
void	save_segment(t_lexer *l, t_token_word **t, char quote);

// TOKEN

t_token		*token(t_token_class class, const char *text, size_t text_len);
// t_token		*token_word(t_lexer *l, const char *text, size_t text_len);
const char	*token_class_name(t_token_class class);

// WORD SEGMENT

t_segment	*segment(t_seg_type type, const char *text, size_t text_len);

#endif //PARSESH_H
