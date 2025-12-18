/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:41:04 by brensant          #+#    #+#             */
/*   Updated: 2025/12/17 23:09:32 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"

char	*expanded_token_text(t_token_word *t)
{
	char		*str;
	t_segment	*seg;

	str = NULL;
	seg = t->seg_lst;
	while (seg && !str)
	{
		if (seg->text)
			str = ft_gcfct_register_root(ft_strdup(seg->text), "temp");
		seg = seg->next;
	}
	while (seg)
	{
		if (seg->text)
			str = ft_gcfct_register_root(ft_strjoin(str, seg->text), "temp");
		seg = seg->next;
	}
	return (str);
}

int	expand_token(t_token_word *t)
{
	t_segment	*seg;
	int			status;

	seg = t->seg_lst;
	status = 0;
	while (seg)
	{
		if (seg->type == VAR_FIXED || seg->type == VAR_SPLIT)
		{
			seg->text = var_exp(seg->text);
			status = 1;
		}
		else if (seg->type == CMD_FIXED || seg->type == CMD_SPLIT)
		{
			// TODO: expandir comando no subshell
			status = 1;
		}
		seg = seg->next;
	}
	return (status);
}

static void	replace_token(t_token_word **target, t_token **prev,
	t_token **token_list)
{
	t_token		*next;
	t_token		*aux;
	char		*new_text;
	t_lexer		l;

	next = (*target)->next;
	new_text = expanded_token_text(*target);
	if (!new_text)
	{
		*prev = (t_token *)*target;
		return ;
	}
	l = lexer_new(new_text, ft_strlen((const char *)new_text));
	aux = lexer_token_list(&l);
	if (*prev)
		(*prev)->next = aux;
	else
		*token_list = aux;
	while (aux->next)
		aux = aux->next;
	aux->next = next;
	*prev = aux;
}

void	expand_token_list(t_token **token_list)
{
	t_token		*head;
	t_token		*prev;

	head = *token_list;
	prev = NULL;
	while (head)
	{
		if (head->class == TOKEN_WORD && expand_token((t_token_word *)head))
			replace_token((t_token_word **)&head, &prev, token_list);
		else
			prev = head;
		head = head->next;
	}
}
