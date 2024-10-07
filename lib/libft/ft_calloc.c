/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:18:32 by apancar           #+#    #+#             */
/*   Updated: 2024/10/03 12:18:33 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	buffsize;

	buffsize = nmemb * size;
	res = malloc(buffsize);
	if (res == NULL)
		return (res);
	ft_bzero(res, buffsize);
	return (res);
}
