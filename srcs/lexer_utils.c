/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:00:52 by brensant          #+#    #+#             */
/*   Updated: 2025/12/06 02:06:25 by brensant         ###   ########.fr       */
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
