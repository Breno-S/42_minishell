/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_prefix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:15:24 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/17 22:08:13 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_prefix(const char *str, const char *prefix)
{
	int	len_str;
	int	i;

	i = 0;
	if (!str || !prefix || ft_strlen(str) < ft_strlen(prefix) || !prefix[0]
		|| !str[0])
		return (-1);
	len_str = ft_strlen(prefix);
	while (str[i] || i < len_str)
	{
		if (str[len_str + i] != prefix[i])
			return (-1);
		i++;
	}
	return (i);
}
