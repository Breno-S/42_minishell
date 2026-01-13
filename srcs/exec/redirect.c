/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:58:20 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/13 20:05:36 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	handle_redirects(t_io_node *redirs, t_exec **exec, t_ast *ast)
{
	while (redirs)
	{
		if (redirs->type == TOKEN_REDIR_INPUT)
			if (open_infile(redirs->io_target->seg_lst->text, exec))
				return (1);
		if (redirs->type == TOKEN_REDIR_OUTPUT)
			if (open_outfile(redirs->io_target->seg_lst->text, exec, 1))
				return (1);
		if (redirs->type == TOKEN_REDIR_APPEND)
			if (open_outfile(redirs->io_target->seg_lst->text, exec, 2))
				return (1);
		if (redirs->type == TOKEN_REDIR_HEREDOC)
			if (open_heredoc(exec, ast))
				return (1);
		redirs = redirs->next;
	}
	return (0);
}

int	open_infile(char *infile, t_exec **exec)
{
	if (exec[0]->infile != -1)
		close(exec[0]->infile);
	exec[0]->infile = open(infile, O_RDONLY);
	if (exec[0]->infile == -1)
	{
		perror("Minishell");
		if (errno == 2)
			return (0);
		return (1);
	}
	return (0);
}

int	open_outfile(char *outfile, t_exec **exec, int type)
{
	if (exec[0]->outfile != -1)
		close(exec[0]->outfile);
	if (type == 1)
		exec[0]->outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		exec[0]->outfile = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (exec[0]->outfile == -1)
	{
		perror("Minishell");
		return (1);
	}
	return (0);
}

int	open_heredoc(t_exec **exec, t_ast *ast)
{
	if (exec[0]->infile != -1)
		close(exec[0]->infile);
	exec[0]->infile = open(ast->heredoc->path, O_RDONLY);
	close(ast->heredoc->fd_tmp);
	ast->heredoc = ast->heredoc->next;
	return (0);
}
