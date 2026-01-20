/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_atom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:57:36 by brensant          #+#    #+#             */
/*   Updated: 2026/01/20 12:52:05 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorsh.h"
#include "execsh.h"
#include "parsesh.h"

static void	normalize_here_target(t_token_word *io_target)
{
	char	*new_text;

	new_text = text_from_segments(io_target->seg_lst);
	io_target->text = new_text;
	io_target->text_len = ft_strlen(new_text);
	io_target->seg_lst->text = new_text;
	remove_null_segs(io_target);
	io_target->seg_lst->next = NULL;
}

static int	expand_args_redirs(t_ast *ast)
{
	char		*curr_text;
	t_io_node	*redir;

	expand_token_list((t_token **)&ast->args);
	redir = ast->redirs;
	while (redir)
	{
		if (redir->type != TOKEN_REDIR_HEREDOC)
		{
			curr_text = ft_gcfct_register_root(ft_substr(redir->io_target->text,
						0, redir->io_target->text_len), "temp");
			expand_token_list((t_token **)&redir->io_target);
			if (!redir->io_target || (redir->io_target->next
					&& redir->io_target->next->class == TOKEN_WORD))
			{
				log_ambiguous_redir_error(curr_text);
				return (0);
			}
		}
		else
			normalize_here_target(ast->redirs->io_target);
		redir = redir->next;
	}
	return (1);
}

int	expand_atom(t_ast *ast)
{
	if (ast->type == NODE_CMD)
	{
		if (expand_args_redirs(ast))
			ast->cmd = build_cmd(ast);
		else
		{
			ast->cmd = ft_gc_calloc_root(1, sizeof(t_exec), "temp");
			return (1);
		}
	}
	else if (ast->type == NODE_SUB)
		ast->cmd = build_sub(ast);
	return (0);
}
