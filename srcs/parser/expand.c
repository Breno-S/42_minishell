/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:41:04 by brensant          #+#    #+#             */
/*   Updated: 2025/12/22 19:49:00 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"

void	remove_null_segs(t_token_word *t)
{
	t_segment	*head;
	t_segment	*prev;

	head = t->seg_lst;
	prev = NULL;
	while (head)
	{
		if ((head->type >= 1 && head->type <= 4)
			&& (!head->text || head->text[0] == '\0'))
			remove_segment(&t->seg_lst, head, prev);
		else
			prev = head;
		head = head->next;
	}
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

void	expand_token_list(t_token **token_list)
{
	t_token	*head;
	t_token	*prev;

	head = *token_list;
	prev = NULL;
	while (head)
	{
		if (head->class == TOKEN_WORD && expand_token((t_token_word *)head))
		{
			remove_null_segs((t_token_word *)head);
			if (((t_token_word *)head)->seg_lst == NULL)
				remove_token(token_list, head, prev);
			else
			{
				split_first_segs((t_token_word *)head);
				split_last_segs((t_token_word *)head);
				join_fixed_segs((t_token_word *)head);
				replace_tokens((t_token_word *)head, &prev, head->next,
					token_list);
			}
		}
		else
			prev = head;
		head = head->next;
	}
}
