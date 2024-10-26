/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:40:32 by apancar           #+#    #+#             */
/*   Updated: 2024/10/26 11:47:49 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	check_f(char **rgb, char *line)
{
	int	i;
	int	count;

	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (1);
	count = 0;
	while (*line)
	{
		if (*line == ',')
			count++;
		line++;
	}
	i = 0;
	while (i < 3 && ft_atoi(rgb[i]) >= 0 && ft_atoi(rgb[i]) <= 255)
		i++;
	if (count != 2 || i != 3)
		return (1);
	return (0);
}

void	parse_color(t_vars *vars, char *line, t_color *color, int **flag)
{
	char	**rgb;
	int		i;

	check_flag(vars, &flag);
	i = 0;
	while (line[i] == ' ')
		i++;
	rgb = ft_split(line + i, ',');
	if (!rgb || ft_is_digit(rgb[0][0]) == 0 || ft_is_digit(rgb[1][0]) == 0
		|| ft_is_digit(rgb[2][0]) == 0)
		dispose_t_map(vars);
	if (check_f(rgb, line + i) == 1)
	{
		free_rgb(rgb);
		dispose_t_map(vars);
	}
	color->red = ft_atoi(rgb[0]);
	color->green = ft_atoi(rgb[1]);
	color->blue = ft_atoi(rgb[2]);
	free_rgb(rgb);
}
