/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_glob.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:05:19 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/17 16:13:21 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

// char *glob_exp(char *glob)
// {
// 	dir = opendir(".");
// 	ent = readdir(dir[0]);
// 	closedir(dir);
// }

t_list	*handle_dir(char *dir)
{
	DIR				*o_dir;
	t_list			*files;
	struct dirent	*ent;

	ent = (struct dirent *){0};
	o_dir = opendir(dir);
	if (!o_dir)
		return (NULL);
	while (1)
	{
		ent = readdir(o_dir);
	}
}

// -> abro dir -> procuro

// ..
// teste

// literal
// pre*suf
// pre*in*in*suf


// ../teste/teste*.c


