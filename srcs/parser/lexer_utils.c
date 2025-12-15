/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:00:52 by brensant          #+#    #+#             */
/*   Updated: 2025/12/12 17:48:08 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"

size_t	lexer_chop_chars(t_lexer *l, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && l->idx < l->str_len)
	{
		i++;
		l->idx++;
		if (l->str[l->idx] == '\"' && !l->squote_flag)
			l->dquote_flag = !l->dquote_flag;
		else if (l->str[l->idx] == '\'' && !l->dquote_flag)
			l->squote_flag = !l->squote_flag;
		else if (l->str[l->idx] == '(')
		{
			if (!l->squote_flag && l->cmd_lvl == 0
				&& l->idx && l->str[l->idx - 1] == '$' )
				l->cmd_lvl++;
		}
		else if (l->str[l->idx] == ')' && l->cmd_lvl)
			l->cmd_lvl--;
	}
	return (i);
}

size_t	lexer_chop_til(t_lexer *l, char *ch_list, size_t limit, size_t *opt_acc)
{
	size_t	len;

	len = 0;
	while (ft_strchr(ch_list, l->str[l->idx]) == NULL
		&& len < limit && l->idx < l->str_len)
		len += lexer_chop_chars(l, 1);
	if (opt_acc)
		*opt_acc += len;
	return (len);
}

size_t	lexer_chop_while(t_lexer *l, char *ch_list, size_t limit,
	size_t *opt_acc)
{
	size_t	len;

	len = 0;
	while (ft_strchr(ch_list, l->str[l->idx]) != NULL
		&& len < limit && l->idx < l->str_len)
		len += lexer_chop_chars(l, 1);
	if (opt_acc)
		*opt_acc += len;
	return (len);
}
