/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:16:26 by apancar           #+#    #+#             */
/*   Updated: 2024/11/05 19:33:07 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_rgb(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}

void	check_flag(t_vars *vars, int ***flag)
{
	if (***flag == 1)
	{
		printf("Error\n");
		free_t_map(vars);
		exit(EXIT_FAILURE);
	}
}

void	dispose_t_map(t_vars *vars)
{
	free_t_map(vars);
	printf("Error\n");
	exit(EXIT_FAILURE);
}

void	parse_texture(t_vars *vars, char *line, char **texture_path, int **flag)
{
	char	*newline_pos;
	char	*temp;
	int		i;

	check_flag(vars, &flag);
	i = 0;
	while (line[i] == ' ')
		i++;
	newline_pos = ft_strchr(line + i, '\n');
	if (newline_pos)
		*newline_pos = '\0';
	*texture_path = ft_strdup(line + i);
	if (*texture_path == NULL)
	{
		printf("Error\n");
		dispose_t_map(vars);
	}
	temp = ft_strjoin(*texture_path, ".xpm");
	if (!temp)
	{
		free(*texture_path);
		printf("Error\n");
		dispose_t_map(vars);
	}
	free(*texture_path);
	*texture_path = temp;
}
