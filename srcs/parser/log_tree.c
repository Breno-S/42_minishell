/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:57:36 by brensant          #+#    #+#             */
/*   Updated: 2026/01/09 21:19:33 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsesh.h"
#include "errorsh.h"
#include "execsh.h"

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
	printf("%.*s", (int)io_node->io_target->text_len, io_node->io_target->text);
	printf("\n");
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

void	traverse_tree(t_ast *ast, int indent, t_hash_env **hash_env)
{
	for (int i = 0; i < indent; i++)
		printf("  ");
	if (ast->type == NODE_CMD)
	{
		expand_token_list((t_token **)&ast->args);

		if (ast->redirs)
		{
			if (ast->redirs->type != TOKEN_REDIR_HEREDOC)
			{
				char *curr_text;

				curr_text = ft_substr(ast->redirs->io_target->text, 0, ast->redirs->io_target->text_len);
				expand_token_list((t_token **)&ast->redirs->io_target);
				if (!ast->redirs->io_target || ast->redirs->io_target->next)
				{
					// TODO: arrumar o retorno
					log_ambiguous_redir_error(curr_text);
					return ;
				}
			}
			else
			{
				normalize_here_target(ast->redirs->io_target);
				// Check for quotes on token->text
			}
		}
		ast->cmd = build_cmd(ast);

		printf("CMD:\n");
		print_args(ast, indent + 1);
		print_redirs(ast, indent + 1);
	}
	else if (ast->type == NODE_AND)
	{
		printf("AND:\n");
		traverse_tree(ast->left, indent + 1, hash_env);
		traverse_tree(ast->right, indent + 1, hash_env);
	}
	else if (ast->type == NODE_OR)
	{
		printf("OR:\n");
		traverse_tree(ast->left, indent + 1, hash_env);
		traverse_tree(ast->right, indent + 1, hash_env);
	}
	else if (ast->type == NODE_PIPE)
	{
		printf("PIPE:\n");
		traverse_tree(ast->left, indent + 1, hash_env);
		traverse_tree(ast->right, indent + 1, hash_env);
	}
	else if (ast->type == NODE_SUB)
	{
		printf("SUB:\n");
		traverse_tree(ast->left, indent + 1, hash_env);
	}
}
