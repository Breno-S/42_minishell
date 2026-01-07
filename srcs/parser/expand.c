/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:41:04 by brensant          #+#    #+#             */
/*   Updated: 2026/01/07 20:34:06 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"
#include "execsh.h"

int	expand_var_segs(t_token_word *token)
{
	t_segment	*seg;
	int			status;

	seg = token->seg_lst;
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

static void	expand_globs(t_token *target, t_token **prev,
	t_token *next, t_token **token_list)
{
	char	*str;
	t_lexer	l;
	t_token	*new_tokens;

	str = glob_exp(target);
	if (str)
	{
		l = lexer_new(str, ft_strlen(str));
		new_tokens = lexer_token_list(&l);
		if (new_tokens)
		{
			if (*prev)
				(*prev)->next = new_tokens;
			else
				(*token_list) = new_tokens;
			while (new_tokens->next)
				new_tokens = new_tokens->next;
			new_tokens->next = next;
			*prev = new_tokens;
		}
	}
}

static void	expand_var(t_token **token_list)
{
	t_token	*token;
	t_token	*prev;

	token = *token_list;
	prev = NULL;
	while (token)
	{
		if (expand_var_segs((t_token_word *)token))
		{
			remove_null_segs((t_token_word *)token);
			if (((t_token_word *)token)->seg_lst == NULL)
				remove_token(token_list, token, prev);
			else
			{
				split_first_segs((t_token_word *)token);
				split_last_segs((t_token_word *)token);
				join_fixed_segs((t_token_word *)token);
				replace_tokens((t_token_word *)token, &prev, token->next,
					token_list);
			}
		}
		else
			prev = token;
		token = token->next;
	}
}

static void	expand_wildcard(t_token **token_list)
{
	t_token	*token;
	t_token	*prev;

	token = *token_list;
	prev = NULL;
	while (token)
	{
		expand_globs(token, &prev, token->next, token_list);
		token = token->next;
	}
}

void	expand_token_list(t_token **token_list)
{
	expand_var(token_list);
	expand_wildcard(token_list);
}
