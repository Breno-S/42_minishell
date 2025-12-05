/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:16:04 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/05 15:58:52 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

char **exp_glob()

int main(void)
{
	DIR *oi;
	struct dirent *tchau;
	oi = opendir(".");
	tchau = readdir(oi);
	while (tchau)
	{
		printf("%s   ", tchau->d_name);
		tchau = readdir(oi);
	}
	closedir(oi);
	printf("\n");
}
