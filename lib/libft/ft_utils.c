/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:19:50 by apancar           #+#    #+#             */
/*   Updated: 2024/10/03 12:19:51 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	degree_to_radian(float degree)
{
	return ((degree / 180) * PI);
}

float	ft_rad_to_deg(float rad)
{
	return (rad * (180 / PI));
}
