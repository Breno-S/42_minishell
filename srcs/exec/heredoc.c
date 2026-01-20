/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:18:32 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/20 16:26:30 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"
#include "signalsh.h"

int	handle_heredoc(t_ast *ast)
{
	t_io_node	*redirs;
	t_heredoc	*heredoc;

	redirs = ast->redirs;
	while ((ast->type == NODE_CMD || ast->type == NODE_SUB) && redirs)
	{
		if (redirs->type == TOKEN_REDIR_HEREDOC)
		{
			heredoc = create_heredoc(redirs->io_target->seg_lst->text);
			if (!heredoc)
				return (1);
			fix_list_heredoc(ast, heredoc);
		}
		redirs = redirs->next;
	}
	return (0);
}

t_heredoc	*create_heredoc(char *eof)
{
	t_heredoc	*heredoc;

	heredoc = ft_gc_calloc_root(1, sizeof(t_heredoc), "temp");
	if (!heredoc)
		return (NULL);
	heredoc->fd_tmp = open("/tmp", O_RDWR | __O_TMPFILE, 0667);
	if (heredoc->fd_tmp == -1)
		return (NULL);
	loop_heredoc(eof, heredoc);
	if (g_signal)
	{
		close(heredoc->fd_tmp);
		return (NULL);
	}
	heredoc->path = access_temp_file(heredoc->fd_tmp);
	if (!heredoc->path)
		return (NULL);
	return (heredoc);
}

int	loop_heredoc(char *eof, t_heredoc *heredoc)
{
	char	*str;
	int		count;

	count = 1;
	set_signal_interactive();
	while (!g_signal)
	{
		if (isatty(STDIN_FILENO))
		{
			rl_event_hook = check_signal_state;
			str = ft_gcfct_register_root(readline("> "), "temp");
			rl_event_hook = NULL;
		}
		else
			str = ft_gcfct_register_root(readline(""), "temp");
		if (!str && !g_signal)
			print_warning(eof, count);
		if ((str && !ft_strcmp(str, eof)) || !str || g_signal)
			break ;
		ft_putendl_fd(str, heredoc->fd_tmp);
		count++;
	}
	return (0);
}

char	*access_temp_file(int tmp)
{
	char	*tmp_char;
	char	*path;

	tmp_char = NULL;
	tmp_char = ft_gcfct_register_root(ft_itoa(tmp), "temp");
	if (!tmp_char)
		return (NULL);
	path = ft_gcfct_register_root(ft_strjoin("/proc/self/fd/", tmp_char),
			"temp");
	if (!path)
		return (NULL);
	return (path);
}

void	print_warning(char *eof, int count)
{
	ft_putstr_fd("\033[0;35mMinishell: warning: here-document at line ", 2);
	ft_putnbr_fd(count, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted '", 2);
	ft_putstr_fd(eof, 2);
	ft_putendl_fd("')\033[0m", 2);
}
