/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:58:20 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/07 18:23:38 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	handle_redirects(t_io_node *redirs, t_exec **exec)
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
			if (open_heredoc(redirs->io_target->seg_lst->text, exec))
				return (1);
		redirs = redirs->next;
	}
	return (0);
}

int	*open_pipeline(t_exec **exec)
{
	int	*pipefd;

	pipefd = ft_gc_malloc(8, GC_DATA)->content;
	if (!pipefd)
	{
		perror("Minishell");
		return (NULL);
	}
	if (pipe(pipefd) == -1)
	{
		perror("Minishell");
		return (NULL);
	}
	return (pipefd);
}

int	open_infile(char *infile, t_exec **exec)
{
	if (exec[0]->infile->fd_tmp != -1)
		close(exec[0]->infile->fd_tmp);
	exec[0]->infile->fd_tmp = open(infile, O_RDONLY);
	if (exec[0]->infile->fd_tmp == -1)
	{
		perror("Minishell");
		return (1);
	}
	return (0);
}

int	open_outfile(char *outfile, t_exec **exec, int type)
{
	if (exec[0]->outfile->fd_tmp != -1)
		close(exec[0]->outfile->fd_tmp);
	if (type == 1)
		exec[0]->outfile->fd_tmp = open(outfile, O_WRONLY | O_TRUNC | O_CREAT,
				0644);
	else
		exec[0]->outfile->fd_tmp = open(outfile, O_WRONLY | O_APPEND | O_CREAT,
				0644);
	if (exec[0]->outfile->fd_tmp == -1)
	{
		perror("Minishell");
		return (1);
	}
	return (0);
}

int	open_heredoc(char *eof, t_exec **exec)
{
	t_redirect	*heredoc;

	if (exec[0]->infile->fd_tmp != -1)
		close(exec[0]->infile->fd_tmp);
	heredoc = create_heredoc(eof);
	exec[0]->infile->fd_tmp = open(heredoc->path, O_RDONLY);
	close(heredoc->fd_tmp);
	if (exec[0]->infile->fd_tmp == -1)
	{
		perror("Minishell");
		return (1);
	}
	return (0);
}
