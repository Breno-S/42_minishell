/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsesh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:22:36 by brensant          #+#    #+#             */
/*   Updated: 2025/12/07 20:16:11 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSESH_H
# define PARSESH_H

# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "types.h"

// LEXER

t_lexer			lexer_new(const char *str, size_t str_len);
int				lexer_starts_with(t_lexer *l, const char *prefix);
void			lexer_chop_char(t_lexer *l, size_t len);
t_token			*lexer_next(t_lexer *l);
t_token			*lexer_token_list(t_lexer *l);

// LEXER UTILS

void			lexer_trim_left(t_lexer *l);
int				is_metachar(char c);

// LEXER AUX

void			handle_metachar(t_lexer *l, t_token **t);
void			handle_word(t_lexer *l, t_token **t);

// TOKEN

t_token			*token(t_token_class class, const char *text, size_t text_len);
t_token			*token_word(const char *text, size_t text_len,
					t_segment *seg_list);
const char		*token_class_name(t_token_class class);
void			token_add(t_token **token_list, t_token *new);

// SEGMENT

t_segment		*segment(t_seg_type type, const char *text, size_t text_len);
void			segment_add(t_segment **seg_list, t_segment *new);

// PARSER

t_parser		parser_new(t_token *token_list);
t_token			*parser_get_token(t_parser *p);
t_token_class	parser_peek(t_parser *p);
void			parser_chop_token(t_parser *p);
t_ast			*parser_parse(t_parser *p);

t_io_node		*io_node(t_token_class type, t_token_word *target);
void			io_node_add(t_io_node **io_node_list, t_io_node *new);

#endif //PARSESH_H
