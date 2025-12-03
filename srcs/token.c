/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:51:43 by brensant          #+#    #+#             */
/*   Updated: 2025/12/03 14:36:08by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

t_token	*token_end(void)
{
	return (ft_calloc(1, sizeof(t_token)));
}

t_token	*token(t_token_class class, const char *text, size_t text_len)
{
	t_token	*t;

	t = ft_gc_calloc_root(1, sizeof(*t), "temp");
	if (!t)
		return (NULL);
	t->class = class;
	t->text = text;
	t->text_len = text_len;
	return (t);
}

// t_token		*token_word(t_lexer *l, const char *text, size_t text_len)
// {
// 	t_token_word *t_word;

// 	t_word = malloc(sizeof(*t_word));
// 	t_word->class = TOKEN_WORD;
// 	t_word->text = text;
// 	t_word->text_len = text_len;
// 	// save_segments();
// 	return ((t_token *)t_word);
// }

t_segment	*segment(t_seg_type type, const char *text, size_t text_len)
{
	t_segment	*seg;

	seg = ft_gc_calloc_root(1, sizeof(*seg), "temp");
	seg->type = type;
	seg->text = ft_gc_calloc_root(1, text_len + 1, "temp");
	if (!seg->text)
		return (NULL);
	ft_strlcpy(seg->text, text, text_len + 1);
	return (seg);
}

const char	*token_class_name(t_token_class class)
{
	switch (class)
	{
		case TOKEN_END:
			return ("end of content");
		case TOKEN_INVALID:
			return ("invalid token");
		case TOKEN_WORD:
			return ("word");
		case TOKEN_PIPE:
			return ("pipe");
		case TOKEN_OPEN_PAREN:
			return ("open parenthesis");
		case TOKEN_CLOSE_PAREN:
			return ("close parenthesis");
		case TOKEN_COMMENT:
			return ("comment");
		case TOKEN_REDIR_INPUT:
			return ("input redirection");
		case TOKEN_REDIR_OUTPUT:
			return ("output redirection");
		case TOKEN_REDIR_APPEND:
			return ("append redirection");
		case TOKEN_REDIR_HEREDOC:
			return ("heredoc");
		case TOKEN_AND:
			return ("AND");
		case TOKEN_OR:
			return ("OR");
	}
	return (NULL);
}
