/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:18:48 by apancar           #+#    #+#             */
/*   Updated: 2024/10/03 12:18:49 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_normalize(float value, float min, float max)
{
	if (max == min)
		return (1);
	return ((value - min) / (max - min));
}

float	linear_interpolation(float value, float min, float max)
{
	return ((value * (max - min)) + min);
}

float	ft_map(float value, t_map map)
{
	return (linear_interpolation(ft_normalize(value, map.min_i, map.min_o),
			map.min_o, map.max_o));
}

t_map	ft_map_init(float min_i, float max_i, float min_o, float max_o)
{
	t_map	map;

	map.max_i = max_i;
	map.max_o = max_o;
	map.min_i = min_i;
	map.min_o = min_o;
	return (map);
}
