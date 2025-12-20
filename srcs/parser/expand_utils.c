/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:03:05 by brensant          #+#    #+#             */
/*   Updated: 2025/12/20 19:11:03 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "execsh.h"

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
		str = ft_gcfct_register_root(ft_strjoin(str, seg->text), "temp");
		seg = seg->next;
	}
	return (str);
}
