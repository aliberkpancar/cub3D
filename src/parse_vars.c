/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:16:26 by apancar           #+#    #+#             */
/*   Updated: 2024/10/03 12:16:27 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_rgb(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
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

static int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	parse_color(t_vars *vars, char *line, t_color *color)
{
	char	**rgb;

	rgb = ft_split(line, ',');
	if (!rgb || ft_is_digit(rgb[0][0]) == 0 || ft_is_digit(rgb[1][0]) == 0
		|| ft_is_digit(rgb[2][0]) == 0)
	{
		free_t_map(vars);
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	if (check_f(rgb, line) == 1)
	{
		free_rgb(rgb);
		printf("Error\nInvalid color format\n");
		free_t_map(vars);
		exit(EXIT_FAILURE);
	}
	color->red = ft_atoi(rgb[0]);
	color->green = ft_atoi(rgb[1]);
	color->blue = ft_atoi(rgb[2]);
	free_rgb(rgb);
}

void	parse_texture(t_vars *vars, char *line, char **texture_path)
{
	char	*newline_pos;
	char	*temp;

	newline_pos = ft_strchr(line, '\n');
	if (newline_pos)
		*newline_pos = '\0';
	*texture_path = ft_strdup(line);
	if (*texture_path == NULL)
	{
		free_t_map(vars);
		perror("Error allocating memory for texture path");
		exit(EXIT_FAILURE);
	}
	temp = ft_strjoin(*texture_path, ".xpm");
	if (!temp)
	{
		free_t_map(vars);
		free(*texture_path);
		perror("Error allocating memory for texture path");
		exit(EXIT_FAILURE);
	}
	free(*texture_path);
	*texture_path = temp;
}
