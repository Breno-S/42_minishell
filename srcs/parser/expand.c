/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:41:04 by brensant          #+#    #+#             */
/*   Updated: 2025/12/16 17:12:34 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "parsesh.h"

char	*expanded_token_text(t_token_word *t)
{
	char		*str;
	t_segment	*seg;

	seg = t->seg_lst;
	if (seg->text)
		str = ft_strdup(seg->text);
	seg = seg->next;
	while(seg)
	{
		if (seg->text)
			ft_strjoin(str, seg->text);
		seg = seg->next;
	}
	return (str);
}

void	expand_token(t_token_word *t)
{
	t_segment	*seg;

	seg = t->seg_lst;
	while (seg)
	{
		if (seg->type == VAR_FIXED || seg->type == VAR_SPLIT)
			seg->text = var_exp(seg->text);
		else if (seg->type == CMD_FIXED || seg->type == CMD_SPLIT)
		{
			// expandir comando no subshell
		}
		seg = seg->next;
	}
}

void	expand_token_list(t_token *token_list)
{
	t_token		*head;
	t_token		*next;
	char		*new_text;
	t_lexer		l;

	head = token_list;
	while (head)
	{
		next = head->next;
		if (head->class == TOKEN_WORD)
		{
			expand_token((t_token_word *)head);
			new_text = expanded_token_text((t_token_word *)head);
			l = lexer_new(new_text, ft_strlen((const char *)new_text));
			head = lexer_token_list(&l);
			while (head->next)
				head = head->next;
			head->next = next;
		}
		head = head->next;
	}
}
