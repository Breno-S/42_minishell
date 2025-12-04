/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:23:28 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/03 19:00:03 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execsh.h>

static int	ft_print_export(int fd);

int	ft_export(const char *var, int fd)
{
	t_list	*env;
	char	**div_var;
	char	*cmp;
	int		len;

	if (!var)
		return(ft_print_export(fd));
	div_var = ft_trim_env((char *)var, '=');
	env = ft_gc_call_root("env")->lst->head;
	len = ft_strlen(div_var[0]);
	while (env)
	{
		cmp = ft_to_gc_list(env->content)->content;
		if (!ft_strncmp(div_var[0], cmp, len) && cmp[len] == '=')
		{
			env->content = ft_gcfct_register(ft_strdup(var), GC_DATA);
			if (!env->content)
				return (1);
			return (0);
		}
		env = env->next;
	}
	if (!ft_gcfct_register_root(ft_strdup(var), "env"))
		return (1);
	return (0);
}

static int	ft_print_export(int fd)
{
	t_list	*env;

	env = ft_gc_call_root("env")->lst->head;
	while (env)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putendl_fd(ft_to_gc_list(env->content)->content, fd);
		env = env->next;
	}
	return (0);
}
