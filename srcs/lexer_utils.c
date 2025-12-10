/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:00:52 by brensant          #+#    #+#             */
/*   Updated: 2025/12/09 21:10:16 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"

void	lexer_trim_left(t_lexer *l)
{
	while (l->idx < l->str_len && ft_isspace(l->str[l->idx]))
		lexer_chop_char(l, 1);
}

int	is_metachar(char c)
{
	if (ft_strchr(" \t\n|&()<>;", c))
		return (1);
	else
		return (0);
}

size_t	lexer_chop_til(t_lexer *l, char *ch_list, size_t limit, size_t *opt_acc)
{
	size_t	len;

	len = 0;
	while (ft_strchr(ch_list, l->str[l->idx]) == NULL && l->idx < l->str_len
		&& len < limit)
	{
		lexer_chop_char(l, 1);
		len++;
	}
	if (opt_acc)
		*opt_acc += len;
	return (len);
}

size_t	lexer_chop_while(t_lexer *l, char *ch_list, size_t limit,
	size_t *opt_acc)
{
	size_t	len;

	len = 0;
	while (ft_strchr(ch_list, l->str[l->idx]) != NULL && l->idx < l->str_len
		&& len < limit)
	{
		lexer_chop_char(l, 1);
		len++;
	}
	if (opt_acc)
		*opt_acc += len;
	return (len);
}
