/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:39:13 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/04 14:53:55 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lenint(unsigned int n)
{
	unsigned int	qt_char;

	qt_char = 0;
	while (n >= 10)
	{
		qt_char++;
		n /= 10;
	}
	qt_char += 1;
	return (qt_char);
}

char	*ft_uitoa(unsigned int n)
{
	unsigned int	i;
	char			*nbr;

	i = ft_lenint(n);
	nbr = (char *)calloc(1, i + 1);
	nbr[i] = 0;
	while (i-- > 0)
	{
		if (n >= 10)
			nbr[i] = (n % 10) + '0';
		else
			nbr[i] = n + '0';
		n /= 10;
	}
	return (nbr);
}
