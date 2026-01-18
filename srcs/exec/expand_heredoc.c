/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:54:37 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/17 23:26:10 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int	open_heredoc_tree(t_ast *ast)
{
	if (!ast)
		return (0);
	if (handle_heredoc(ast))
		return (1);
	if (open_heredoc_tree(ast->left))
		return (1);
	if (open_heredoc_tree(ast->right))
		return (1);
	return (0);
}

void	fix_list_heredoc(t_ast *ast, t_heredoc *heredoc)
{
	t_heredoc	*aux;

	aux = NULL;
	if (!ast->heredoc)
		ast->heredoc = heredoc;
	else
	{
		aux = ast->heredoc;
		while (aux->next)
			aux = aux->next;
		aux->next = heredoc;
	}
}

int	expand_heredoc(t_heredoc *heredoc)
{
	int		fd_hr;
	char	*str;
	char	*buffer;

	fd_hr = open(heredoc->path, O_RDONLY);
	if (fd_hr == -1)
		return (1);
	buffer = ft_gc_calloc(1, 1, GC_DATA)->content;
	if (!buffer)
		return (1);
	while (1)
	{
		str = get_next_line(fd_hr);
		if (!str)
			break ;
		buffer = ft_gcfct_register(ft_strjoin(buffer, str), GC_DATA)->content;
		free(str);
		if (!buffer)
			return (1);
	}
	close(fd_hr);
	verify_text(buffer, heredoc);
	return (0);
}

int	verify_text(char *str, t_heredoc *heredoc)
{
	int	fd_hr;
	int	i;
	int	y;

	fd_hr = open(heredoc->path, O_RDWR, O_TRUNC);
	if (fd_hr == -1)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			y = exp_heredoc(&str[i], fd_hr);
			if (y == -1)
				return (1);
			else if (y == 0)
				write(fd_hr, &str[i], 1);
			i += y;
		}
		else
			write(fd_hr, &str[i], 1);
		i++;
	}
	close(fd_hr);
	return (0);
}

int	exp_heredoc(char *str, int fd_hr)
{
	int		i;
	char	*exp;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		i++;
		if (i == 1 && ft_isdigit(str[i]))
			break ;
		else if (i >= 1 && !(ft_isalnum(str[i]) || str[i] == '_'))
		{
			i--;
			break ;
		}
	}
	if (i)
	{
		exp = ft_gcfct_register(ft_substr(str, 1, i), GC_DATA)->content;
		if (!exp)
			return (-1);
		exp = var_exp(exp);
		if (exp)
			write(fd_hr, exp, ft_strlen(exp));
	}
	return (i);
}
