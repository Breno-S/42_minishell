/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:23:28 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/01 21:07:22 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execsh.h>

void ft_export(char **envp, char **cmd)
{
	ft_gc_call_root("env")->lst->head->content;
	ft_gc_calloc_root(1,sizeof(char)*10, "env");
}
