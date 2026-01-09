/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:41:04 by brensant          #+#    #+#             */
/*   Updated: 2026/01/08 19:47:08 by brensant         ###   ########.fr       */
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
	remove_null_segs(token);
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

static void	insert_wildcard_seg(t_segment *curr, t_segment *next)
{
	t_segment	*w_seg;
	t_segment	*new_seg;
	size_t		i;

	i = 0;
	if (curr->text[0] == '*' && curr->text[1] == '\0')
	{
		curr->type = WILDCARD;
		return ;
	}
	while (curr->text[i])
	{
		if (curr->text[i] == '*')
		{
			w_seg = segment(WILDCARD, &curr->text[i], 1);
			curr->text[i] = '\0';
			curr->next = w_seg;
			new_seg = segment(LITERAL, &curr->text[i + 1], ft_strlen(&curr->text[i + 1]));
			w_seg->next = new_seg;
			new_seg->next = next;
			return ;
		}
		i++;
	}
}

void	isolate_wildcards(t_token_word *token)
{
	t_segment	*seg;

	seg = token->seg_lst;
	while (seg)
	{
		if (seg->type != VAR_FIXED && seg->type != CMD_FIXED)
			insert_wildcard_seg(seg, seg->next);
		seg = seg->next;
	}
	remove_null_segs(token);
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
			if (((t_token_word *)token)->seg_lst == NULL)
				remove_token(token_list, token, prev);
			else
			{
				split_first_segs((t_token_word *)token);
				split_last_segs((t_token_word *)token);
				isolate_wildcards((t_token_word*)token);
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
		if (token->class == TOKEN_WORD)
			expand_globs(token, &prev, token->next, token_list);
		else
			prev = token;
		token = token->next;
	}
}

void	expand_token_list(t_token **token_list)
{
	expand_var(token_list);
	expand_wildcard(token_list);
}
