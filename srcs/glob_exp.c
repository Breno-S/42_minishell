/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:16:04 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/09 14:15:29 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int		aux_exp_glob(DIR **dir, char ***files);
char	**exp_glob(void);

char	**exp_glob(void)
{
	DIR		*dir;
	char	**files;

	files = ft_calloc(1, 8);
	if (!files)
		return (NULL);
	dir = opendir(".");
	if (!dir)
	{
		free(files);
		return (NULL);
	}
	if (!aux_exp_glob(&dir, &files))
	{
		closedir(dir);
		if (!ft_gcfct_register_root(files, "temp"))
			return (NULL);
	}
	else
	{
		closedir(dir);
		return (NULL);
	}
	return (files);
}

int	aux_exp_glob(DIR **dir, char ***files)
{
	struct dirent	*ent;
	char			*file;
	size_t			i;

	i = 1;
	ent = (struct dirent *){0};
	while (1)
	{
		ent = readdir(dir[0]);
		if (!ent)
			break ;
		if (ent->d_name[0] != '.')
		{
			file = ft_gcfct_register_root(ft_strdup(ent->d_name), "temp");
			if (!file)
				free(files[0]);
			if (!file)
				return (1);
			ft_realloc((void **)files, i + 1, 8, (i * 8));
			if (!files[0])
				return (1);
			files[0][(i++) - 1] = file;
		}
	}
	return (0);
}
