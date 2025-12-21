/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsesh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:22:36 by brensant          #+#    #+#             */
/*   Updated: 2025/12/21 19:09:14 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSESH_H
# define PARSESH_H

# include "types.h"

# define WHITESPACE "\t\n\v\f\r "
# define METACHARS " \t\n|&;()<>"
# define VAR_START_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"

// LEXER

t_lexer			lexer_new(const char *str, size_t str_len);
int				lexer_starts_with(t_lexer *l, const char *prefix);
t_token			*lexer_next(t_lexer *l);
t_token			*lexer_token_list(t_lexer *l);

// LEXER UTILS

size_t			lexer_chop_chars(t_lexer *l, size_t len);
size_t			lexer_chop_til(t_lexer *l, char *ch_list, size_t limit,
					size_t *opt_acc);
size_t			lexer_chop_while(t_lexer *l, char *ch_list, size_t limit,
					size_t *opt_acc);

// LEXER AUX

t_token			*handle_metachar(t_lexer *l);
t_token			*handle_word(t_lexer *l);

// TOKEN

t_token			*token(t_token_class class, const char *text, size_t text_len);
t_token			*token_word(const char *text, size_t text_len,
					t_segment *seg_list);
const char		*token_class_name(t_token_class class);
void			token_add(t_token **token_list, t_token *new);

// SEGMENT

t_segment		*segment(t_seg_type type, const char *text, size_t seg_len);
void			segment_add(t_segment **seg_list, t_segment *new);

// PARSER

t_parser		parser_new(t_token *token_list);
void			parser_chop_token(t_parser *p);
t_token_class	parser_peek(t_parser *p);

t_ast			*parser_parse(t_parser *p);

t_ast			*parse_atom(t_parser *p);
t_ast			*parse_cmd(t_parser *p);
t_ast			*parse_sub(t_parser *p);
t_ast			*parse_pipe(t_parser *p);
t_ast			*parse_cond(t_parser *p);

int				parse_redirs(t_parser *p, t_ast *ast);

t_io_node		*io_node(t_token_class type, t_token_word *target);
void			io_node_add(t_io_node **io_node_list, t_io_node *new);

// EXPANSION

int				expand_token(t_token_word *t);
void			expand_token_list(t_token **token_list);

void			remove_null_segs(t_token_word *t);
void			replace_tokens(t_token_word *target, t_token **prev,
					t_token *next, t_token **token_list);

void			split_first_segs(t_token_word *t);
void			split_last_segs(t_token_word *t);
void			join_fixed_segs(t_token_word *t);

void			remove_segment(t_segment **seg_lst, t_segment *target,
					t_segment *prev);
void			remove_token(t_token **token_list, t_token *target,
					t_token *prev);
char			*text_from_segments(t_segment *seg_lst);

#endif //PARSESH_H
