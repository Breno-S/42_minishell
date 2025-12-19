/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:41:04 by brensant          #+#    #+#             */
/*   Updated: 2025/12/18 21:17:42 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "parsesh.h"

// char	*expanded_token_text(t_token_word *t)
// {
// 	char		*str;
// 	t_segment	*seg;

// 	str = NULL;
// 	seg = t->seg_lst;
// 	while (seg && !str)
// 	{
// 		if (seg->text)
// 			str = ft_gcfct_register_root(ft_strdup(seg->text), "temp");
// 		seg = seg->next;
// 	}
// 	while (seg)
// 	{
// 		if (seg->text)
// 			str = ft_gcfct_register_root(ft_strjoin(str, seg->text), "temp");
// 		seg = seg->next;
// 	}
// 	return (str);
// }

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

static t_token_word	*get_new_tokens(t_segment *seg_lst)
{
	t_segment		*new_segs;
	t_token_word	*new_tokens;

	new_segs = NULL;
	new_tokens = NULL;
	while (seg_lst)
	{
		if (seg_lst == WILDCARD)
			segment_add(&new_segs, segment(WILDCARD, seg_lst->text, ft_strlen(seg_lst->text)));
		else if (seg_lst->type != VAR_SPLIT && seg_lst->type != CMD_SPLIT)
		{
			if (new_segs->type == LITERAL && new_segs->text && seg_lst->text)
				new_segs->text = ft_gcfct_register_root(ft_strjoin(new_segs->text, seg_lst->text), "temp");
			else if (seg_lst->text)
				segment_add(&new_segs, segment(seg_lst->type, seg_lst->text, ft_strlen(seg_lst->text)));
		}
		else if (seg_lst->text)
		{
			ft_substr(seg_lst->text, 0, ft_strchr(seg_lst->text, ' ') - &seg_lst->text[0]);
			new_segs->text = ft_gcfct_register_root(ft_strjoin(new_segs->text, seg_lst->text), "temp");
		}
		seg_lst = seg_lst->next;
	}
	return (new_tokens);
}

static void	replace_tokens(t_token_word **target, t_token **prev,
	t_token *next, t_token **token_list)
{
	t_token_word	*new_tokens;

	new_tokens = get_new_tokens((*target)->seg_lst);
	if (*prev)
		(*prev)->next = new_tokens;
	else
		*token_list = new_tokens;
	while (new_tokens->next)
		new_tokens = new_tokens->next;
	new_tokens->next = next;
	*prev = new_tokens;
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
			replace_tokens((t_token_word **)&head, &prev, head->next, token_list);
		else
			prev = head;
		head = head->next;
	}
}
