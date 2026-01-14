/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:57:36 by brensant          #+#    #+#             */
/*   Updated: 2026/01/14 15:34:10 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorsh.h"
#include "execsh.h"
#include "parsesh.h"

static void	print_token(t_token *t)
{
	printf("%*s", (int)t->text_len - 1, t->text);
}

static void	print_token_word(t_token_word *t)
{
	t_segment	*seg;

	seg = t->seg_lst;
	while (seg)
	{
		printf("%s", seg->text);
		seg = seg->next;
	}
}

static void	print_redir(t_io_node *io_node, int indent)
{
	for (int i = 0; i < indent; i++)
		printf("  ");
	if (io_node->type == TOKEN_REDIR_INPUT)
		printf("<");
	else if (io_node->type == TOKEN_REDIR_OUTPUT)
		printf(">");
	else if (io_node->type == TOKEN_REDIR_HEREDOC)
		printf("<<");
	else if (io_node->type == TOKEN_REDIR_APPEND)
		printf(">>");
	printf(" ");
	if (io_node->io_target)
		printf("%.*s\n", (int)io_node->io_target->text_len, io_node->io_target->text);
}

static void	print_redirs(t_ast *ast, int indent)
{
	t_io_node	*redirs;

	if (!ast || !ast->redirs)
		return ;
	redirs = ast->redirs;
	while (redirs)
	{
		print_redir(redirs, indent);
		redirs = redirs->next;
	}
}

static void	print_args(t_ast *ast, int indent)
{
	t_token_word	*args;

	if (!ast)
		return ;
	for (int i = 0; i < indent; i++)
		printf("  ");
	args = ast->args;
	while (args)
	{
		print_token_word(args);
		printf(" ");
		args = (t_token_word *)args->next;
	}
	printf("\n");
}

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
			if (!redir->io_target || redir->io_target->next)
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

int	traverse_expand(t_ast *ast, int indent, t_hash_env **hash_env)
{
	for (int i = 0; i < indent; i++)
		printf("  ");
	if (ast->type == NODE_CMD)
	{
		if (expand_args_redirs(ast))
			ast->cmd = build_cmd(ast);
		else
			return (0);
		printf("CMD:\n");
		print_args(ast, indent + 1);
		print_redirs(ast, indent + 1);
	}
	else if (ast->type == NODE_AND)
	{
		printf("AND:\n");
		traverse_expand(ast->left, indent + 1, hash_env);
		traverse_expand(ast->right, indent + 1, hash_env);
	}
	else if (ast->type == NODE_OR)
	{
		printf("OR:\n");
		traverse_expand(ast->left, indent + 1, hash_env);
		traverse_expand(ast->right, indent + 1, hash_env);
	}
	else if (ast->type == NODE_PIPE)
	{
		printf("PIPE:\n");
		traverse_expand(ast->left, indent + 1, hash_env);
		traverse_expand(ast->right, indent + 1, hash_env);
	}
	else if (ast->type == NODE_SUB)
	{
		printf("SUB:\n");
		traverse_expand(ast->left, indent + 1, hash_env);
	}
	return (1);
}
