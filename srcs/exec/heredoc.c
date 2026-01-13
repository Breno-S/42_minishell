/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:18:32 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/12 23:04:35 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

t_redirect	*create_heredoc(char *eof)
{
	t_redirect	*heredoc;
	char		*str;
	int			count;

	heredoc = ft_gc_calloc_root(1, sizeof(t_redirect), "temp");
	if (!heredoc)
		return (NULL);
	heredoc->fd_tmp = open("/tmp", O_RDWR | __O_TMPFILE, 0667);
	if (heredoc->fd_tmp == -1)
		return (NULL);
	count = 0;
	while (1)
	{
		str = ft_gcfct_register_root(readline("> "), "`temp");
		if (!str)
			print_warning(eof, count);
		if ((str && !ft_strcmp(str, eof)) || !str)
			break ;
		ft_putendl_fd(str, heredoc->fd_tmp);
		count++;
	}
	heredoc->path = access_temp_file(heredoc->fd_tmp);
	if (!heredoc->path)
		return (NULL);
	return (heredoc);
}

char	*access_temp_file(int tmp)
{
	char	*tmp_char;
	char	*path;

	tmp_char = NULL;
	tmp_char = ft_gcfct_register_root(ft_itoa(tmp), "`temp");
	if (!tmp_char)
		return (NULL);
	path = ft_gcfct_register_root(ft_strjoin("/proc/self/fd/", tmp_char),
			"here_tmp");
	if (!path)
		return (NULL);
	return (path);
}

void	print_warning(char *eof, int count)
{
	ft_putstr_fd("Minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(count, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted '", 2);
	ft_putstr_fd(eof, 2);
	ft_putstr_fd("')\n", 2);
}
