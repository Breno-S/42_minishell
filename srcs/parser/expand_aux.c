/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 18:56:27 by brensant          #+#    #+#             */
/*   Updated: 2025/12/20 20:18:35 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"
#include "types.h"

static void	remove_segment(t_segment *seg_lst, t_segment *target,
	t_segment *prev)
{
	if (prev)
		prev->next = target->next;
	else
		seg_lst = target->next;
}

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
			remove_segment(t->seg_lst, head, prev);
		else
			prev = head;
		head = head->next;
	}
}

void	join_fixed_segs(t_token_word *t)
{
	t_segment	*head;
	t_segment	*prev;

	head = t->seg_lst;
	prev = NULL;
	while (head->next)
	{
		if ((head->type == LITERAL || head->type == VAR_FIXED
				|| head->type == CMD_FIXED) && (head->next->type == LITERAL
				|| head->next->type == VAR_FIXED
				|| head->next->type == CMD_FIXED))
		{
			head->type = LITERAL;
			head->text = ft_gcfct_register_root(
					ft_strjoin(head->text, head->next->text), "temp");
			remove_segment(t->seg_lst, head->next, head);
			continue ;
		}
		else
			prev = head;
		head = head->next;
	}
}

void	replace_tokens(t_token_word *target, t_token **prev,
	t_token *next, t_token **token_list)
{
	t_token		*new_tokens;
	char		*new_prompt;
	t_lexer		l;

	new_prompt = expanded_token_text(target);
	l = lexer_new(new_prompt, ft_strlen(new_prompt));
	new_tokens = lexer_token_list(&l);
	if (*prev)
		(*prev)->next = new_tokens;
	else
		*token_list = new_tokens;
	while (new_tokens->next)
		new_tokens = new_tokens->next;
	new_tokens->next = next;
	*prev = new_tokens;
}
