/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:16:04 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/05 21:00:49 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

char	**exp_glob(t_segment segment)
{
	DIR				*dir;
	struct dirent	*ent;
	char			**files;
	int	i;

	i = 1;
	files = ft_calloc(1, 8);
	if (!files)
		return (1);
	dir = opendir(".");
	ent = readdir();
}

int	main(void)
{
	DIR				*oi;
	struct dirent	*tchau;
	char *dup;

	oi = opendir(".");
	tchau = readdir(oi);
	dup = ft_strdup(tchau->d_name);
	ft_realloc((void **)&dup, 1, 20);
	dup[1] = 'a';
	printf("%s   \n", dup);
	while (tchau)
	{
		printf("%s   ", tchau->d_name);
		tchau = readdir(oi);
	}
	closedir(oi);
	free(dup);
	printf("\n");
}
