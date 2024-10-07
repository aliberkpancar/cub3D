/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:18:44 by apancar           #+#    #+#             */
/*   Updated: 2024/10/03 12:18:45 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digitcount(int x)
{
	int	count;

	count = 0;
	if (x < 0)
	{
		count++;
		x = -x;
	}
	while (x > 0)
	{
		x = x / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		count;

	count = ft_digitcount(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = malloc(count + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	i = count;
	while (n > 0 && i--)
	{
		str[i] = '0' + (n % 10);
		n = n / 10;
	}
	str[count] = '\0';
	return (str);
}
