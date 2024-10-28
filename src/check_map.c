/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:33 by apancar           #+#    #+#             */
/*   Updated: 2024/10/28 14:20:07 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_char(t_vars *vars, char c)
{
	if (c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != '1'
		&& c != '*' && c != 'B' && c != '0' && c != ' ' && c != '\t'
		&& c != '\n' && c != '\0')
	{
		printf("Error\nInvalid character in the map: %c\n", c);
		free_t_map(vars);
		free_r_map(vars);
		exit(EXIT_FAILURE);
	}
}

static void	fill_flood(t_vars *vars, int y, int x)
{
	if (y < 0 || x < 0 || y >= vars->height || x >= vars->width)
		return ;
	if (vars->r_map[y][x] == 'B')
		return ;
	if (vars->r_map[y][x] == '0' || vars->r_map[y][x] == '1'
		|| vars->r_map[y][x] == 'W' || vars->r_map[y][x] == 'E'
		|| vars->r_map[y][x] == 'N' || vars->r_map[y][x] == 'S')
	{
		vars->r_map[y][x] = '2';
		fill_flood(vars, y + 1, x);
		fill_flood(vars, y - 1, x);
		fill_flood(vars, y, x + 1);
		fill_flood(vars, y, x - 1);
	}
}

static void	check_fill(t_vars *vars)
{
	int	i;
	int	j;

	fill_flood(vars, vars->player.pos.y, vars->player.pos.x);
	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			if (vars->r_map[i][j] == '0' || vars->r_map[i][j] == '1'
				|| vars->r_map[i][j] == 'W' || vars->r_map[i][j] == 'E'
				|| vars->r_map[i][j] == 'N' || vars->r_map[i][j] == 'S')
			{
				printf("Error\nMultiple maps\n");
				free_all(vars, 0);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}

void	check_r_map(t_vars *vars)
{
	int	i;
	int	j;

	get_player_positions(vars);
	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			if (!(vars->r_map[i][0] == 'B' || vars->r_map[i][0] == '1'))
			{
				printf("Error\n");
				free_t_map(vars);
				free_r_map(vars);
				exit(EXIT_FAILURE);
			}
			check_char(vars, vars->r_map[i][j]);
			j++;
		}
		i++;
	}
	check_fill(vars);
}
