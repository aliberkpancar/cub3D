/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:20:01 by apancar           #+#    #+#             */
/*   Updated: 2024/10/03 12:20:02 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

t_vec	ft_vec_inversion(t_vec vector)
{
	t_vec	vec2_inverted;

	vec2_inverted.x = -vector.x;
	vec2_inverted.y = -vector.y;
	return (vec2_inverted);
}

t_vec	ft_vec_norm(t_vec vector)
{
	return (ft_vec_div(vector, ft_vec_mag(vector)));
}

t_vec	ft_vec_rotate(t_vec vector, float degree)
{
	t_vec	rotated_vector;
	float	radian;

	radian = degree_to_radian(degree);
	rotated_vector.x = ((vector.x * cos(radian)) - (vector.y * sin(radian)));
	rotated_vector.y = ((vector.x * sin(radian)) + (vector.y * cos(radian)));
	return (rotated_vector);
}
