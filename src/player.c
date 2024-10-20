/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:16:34 by apancar           #+#    #+#             */
/*   Updated: 2024/10/16 15:23:21 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	ft_strchr_player(const char *s, int c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	get_player_positions(t_vars *vars)
{
	int		i;
	int		j;

	i = 0;
	while (i < vars->temp_height)
	{
		j = 0;
		while (j < vars->temp_width - 1)
		{
			if (ft_strchr_player("NSEW", vars->t_map[i][j]))
			{
				vars->player_count++;
				vars->player.pos = (t_vec){.x = j + 0.5, .y = i + 0.5};
			}
			j++;
		}
		i++;
	}
	if (vars->player_count != 1)
	{
		printf("Error\nInvalid player count\n");
		free_t_map(vars);
		free_r_map(vars);
		exit(EXIT_FAILURE);
	}
}
