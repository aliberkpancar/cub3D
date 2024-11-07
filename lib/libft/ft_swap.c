/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:19:45 by apancar           #+#    #+#             */
/*   Updated: 2024/11/07 12:47:01 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	swap_integers(int *a, int *b)
{
	if (!a || !b)
	{
		printf("Error\n");
		return ;
	}
	if (a == b)
		return ;
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}
