/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:40:32 by apancar           #+#    #+#             */
/*   Updated: 2024/11/07 15:19:58 by apancar          ###   ########.fr       */
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

static void	check_rgb(char **rgb)
{
	int	i;
	int	j;

	i = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (ft_is_digit(rgb[i][j]) == 0)
			{
				free_rgb(rgb, 1);
				exit(1);
			}
			j++;
		}
		i++;
	}
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
	if (!rgb || !rgb[0] || ft_is_digit(rgb[0][0]) == 0 || !rgb[1] \
	|| ft_is_digit(rgb[1][0]) == 0 || !rgb[2] || ft_is_digit(rgb[2][0]) == 0)
	{
		free_rgb(rgb, 1);
		dispose_t_map(vars, 0);
	}
	if (check_f(rgb, line + i) == 1)
	{
		free_rgb(rgb, 1);
		dispose_t_map(vars, 0);
	}
	check_rgb(rgb);
	color->red = ft_atoi(rgb[0]);
	color->green = ft_atoi(rgb[1]);
	color->blue = ft_atoi(rgb[2]);
	free_rgb(rgb, 0);
}

void	check_instructions(int i[], int fd, t_vars *vars)
{
	int	j;

	j = 0;
	while (j < 6)
	{
		if (i[j] == 0)
		{
			close(fd);
			dispose_t_map(vars, 1);
		}
		j++;
	}
}
