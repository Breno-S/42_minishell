/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:03:05 by brensant          #+#    #+#             */
/*   Updated: 2026/01/07 20:33:48 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "execsh.h"

void	remove_segment(t_segment **seg_lst, t_segment *target,
	t_segment *prev)
{
	if (prev)
		prev->next = target->next;
	else
		*seg_lst = target->next;
}

void	remove_null_segs(t_token_word *token)
{
	t_segment	*seg;
	t_segment	*prev;

	seg = token->seg_lst;
	prev = NULL;
	while (seg)
	{
		if ((seg->type >= 1 && seg->type <= 4)
			&& (!seg->text || seg->text[0] == '\0'))
			remove_segment(&token->seg_lst, seg, prev);
		else
			prev = seg;
		seg = seg->next;
	}
}

void	remove_token(t_token **token_list, t_token *target, t_token *prev)
{
	if (prev)
		prev->next = target->next;
	else
		*token_list = target->next;
}

char	*text_from_segments(t_segment *seg_lst)
{
	char		*str;

	str = NULL;
	while (seg_lst && !str)
	{
		if (seg_lst->text)
			str = ft_gcfct_register_root(ft_strdup(seg_lst->text), "temp");
		seg_lst = seg_lst->next;
	}
	while (seg_lst)
	{
		str = ft_gcfct_register_root(ft_strjoin(str, seg_lst->text), "temp");
		seg_lst = seg_lst->next;
	}
	return (str);
}
