/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_glob.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:05:19 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/18 00:20:14 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

// char *glob_exp(char *glob)
// {
// 	dir = opendir(".");
// 	ent = readdir(dir[0]);
// 	closedir(dir);
// }

// t_list	*all_ocult_files(void)
// {
// }

t_list	*all_files(int type)
{
	DIR				*o_dir;
	t_list			*files;
	struct dirent	*ent;
	int				i;

	files = NULL;
	i = 0;
	o_dir = opendir(".");
	if (!o_dir)
		return (NULL);
	while (1)
	{
		ent = readdir(o_dir);
		if (!ent)
			break ;
		if (i++ > 1 && save_files(ent, type, &files))
		{
			closedir(o_dir);
			return (NULL);
		}
	}
	closedir(o_dir);
	return (files);
}

int	save_files(struct dirent *ent, int type, t_list **head)
{
	t_list	*files;
	char	*file;
	int		cmp;

	cmp = (ft_strncmp(ent->d_name, ".", 1) != 0);
	if (cmp != type)
		return (0);
	file = ft_gcfct_register(ft_strdup(ent->d_name), GC_DATA)->content;
	if (!file)
		return (1);
	files = ft_gcfct_register(ft_lstnew(file), GC_DATA)->content;
	if (!files)
		return (1);
	ft_lstadd_back(head, files);
	return (0);
}

// -> abro dir -> procuro

// ..
// teste

// literal
// pre*suf
// pre*in*in*suf

// ../teste/teste*.c
