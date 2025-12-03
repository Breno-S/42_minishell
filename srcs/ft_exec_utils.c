/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:24:08 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/02 22:26:26 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

int export_env(char **arr)
{
	int	i;
	char *str;

	i = 0;
	while (arr[i])
	{
		str = ft_gcfct_register_root(ft_strdup(arr[i++]), "env");
		if (!str)
			return (1);
	}
	return(0);
}

char	**ft_trim_env(char *envp, char sep)
{
	char	**var;
	int		pos_sep;

	var = ft_gc_calloc(2, sizeof(char *), GC_DATA)->content;
	if (!var)
		return (NULL);
	pos_sep = ft_strchr(envp, sep) - envp;
	var[0] = ft_gc_calloc(1, pos_sep + 1, GC_DATA)->content;
	if (!var[0])
		return (NULL);
	ft_strlcpy(var[0], envp, pos_sep + 1);
	var[1] = ft_gcfct_register(ft_strdup(&envp[pos_sep + 1]), GC_DATA)->content;
	if (!var[1])
		return (NULL);
	return (var);
}
