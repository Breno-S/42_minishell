/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:51:43 by brensant          #+#    #+#             */
/*   Updated: 2026/01/11 14:19:52 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

char	*token_to_str(t_token *t)
{
	if (t->class == TOKEN_PIPE)
		return (ft_gcfct_register_root(ft_strdup("|"), "temp"));
	else if (t->class == TOKEN_OPEN_PAREN)
		return (ft_gcfct_register_root(ft_strdup("("), "temp"));
	else if (t->class == TOKEN_CLOSE_PAREN)
		return (ft_gcfct_register_root(ft_strdup(")"), "temp"));
	else if (t->class == TOKEN_REDIR_INPUT)
		return (ft_gcfct_register_root(ft_strdup("<"), "temp"));
	else if (t->class == TOKEN_REDIR_OUTPUT)
		return (ft_gcfct_register_root(ft_strdup(">"), "temp"));
	else if (t->class == TOKEN_REDIR_APPEND)
		return (ft_gcfct_register_root(ft_strdup(">>"), "temp"));
	else if (t->class == TOKEN_REDIR_HEREDOC)
		return (ft_gcfct_register_root(ft_strdup("<<"), "temp"));
	else if (t->class == TOKEN_AND)
		return (ft_gcfct_register_root(ft_strdup("&&"), "temp"));
	else if (t->class == TOKEN_AND)
		return (ft_gcfct_register_root(ft_strdup("||"), "temp"));
	else if (t->class == TOKEN_NEWLINE)
		return (ft_gcfct_register_root(ft_strdup("newline"), "temp"));
	else
		return (NULL);
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

t_token	*token_word(const char *text, size_t text_len, t_segment *seg_list)
{
	t_token_word	*t;

	t = ft_gc_calloc_root(1, sizeof(*t), "temp");
	if (!t)
		return (NULL);
	t->class = TOKEN_WORD;
	t->text = text;
	t->text_len = text_len;
	t->seg_lst = seg_list;
	return ((t_token *)t);
}

void	token_add(t_token **token_list, t_token *new)
{
	t_token	*head;

	if (!token_list)
		return ;
	if (!*token_list)
		*token_list = new;
	else
	{
		head = *token_list;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}
