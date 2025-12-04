/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:23:28 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/03 12:20:50 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execsh.h>

int	ft_unset(const char *var)
{
	t_list	*env;
	char	*cmp;
	int		len;

	env = ft_gc_call_root("env")->lst->head;
	if (!var)
		return (1);
	len = ft_strlen(var);
	while (env)
	{
		cmp = ft_to_gc_list(env->content)->content;
		if (!ft_strncmp(var, cmp, len) && cmp[len] == '=')
		{
			ft_gc_rm_root(&ft_gc_call_root("env")->lst, env);
			return (0);
		}
		env = env->next;
	}
	ft_gc_collect();
	return (0);
}
