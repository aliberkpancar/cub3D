/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:53 by apancar           #+#    #+#             */
/*   Updated: 2024/10/28 14:19:03 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_t_map(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->temp_height)
	{
		free(vars->t_map[i]);
		i++;
	}
	free(vars->t_map);
}

void	free_r_map(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->temp_height)
	{
		free(vars->r_map[i]);
		i++;
	}
	free(vars->r_map);
}

void	free_all(t_vars *vars, int flag)
{
	int	i;

	i = 0;
	while (i < vars->temp_height)
	{
		free(vars->t_map[i]);
		i++;
	}
	free(vars->t_map);
	i = 0;
	while (i < vars->height)
	{
		free(vars->r_map[i]);
		i++;
	}
	if (flag == 1)
		free(vars->map.tiles);
	free(vars->r_map);
	free_textures(vars);
}

void	free_textures(t_vars *vars)
{
	if (vars->texture.east)
	{
		free(vars->texture.east);
		vars->texture.east = NULL;
	}
	if (vars->texture.west)
	{
		free(vars->texture.west);
		vars->texture.west = NULL;
	}
	if (vars->texture.north)
	{
		free(vars->texture.north);
		vars->texture.north = NULL;
	}
	if (vars->texture.south)
	{
		free(vars->texture.south);
		vars->texture.south = NULL;
	}
}
