/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:56:59 by buozcan           #+#    #+#             */
/*   Updated: 2024/07/20 09:01:30 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_swap_int(int *a, int *b)
{
	if (!a || !b)
	{
		printf("Error: ft_swap_int: NULL pointer\n");	
		return ;
	}
	if (a == b)
		return ;
		
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}
