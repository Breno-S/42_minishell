/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:59:46 by brensant          #+#    #+#             */
/*   Updated: 2025/12/09 19:22:00 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"

t_segment	*segment(t_seg_type type, const char *text, size_t seg_len)
{
	t_segment	*seg;

	if (seg_len == 0)
		return (NULL);
	seg = ft_gc_calloc_root(1, sizeof(*seg), "temp");
	if (!seg)
		return (NULL);
	seg->type = type;
	seg->text = ft_gc_calloc_root(1, seg_len + 1, "temp");
	if (!seg->text)
		return (NULL);
	ft_strlcpy(seg->text, text, seg_len + 1);
	return (seg);
}

void	segment_add(t_segment **seg_list, t_segment *new)
{
	t_segment	*head;

	if (!seg_list || !new)
		return ;
	if (!*seg_list)
		*seg_list = new;
	else
	{
		head = *seg_list;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}
