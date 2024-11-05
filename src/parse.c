/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:16:30 by apancar           #+#    #+#             */
/*   Updated: 2024/11/05 19:35:22 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdbool.h>

t_bool	has_special_digits(char *line)
{
	while (*line)
	{
		if (*line == '0' || *line == '1')
			return (true);
		line++;
	}
	return (false);
}

t_bool	has_special_chars(char *line)
{
	while (*line)
	{
		if (*line == 'F' || *line == 'C')
			return (true);
		line++;
	}
	return (false);
}

t_bool	has_special_b(char *line)
{
	while (*line)
	{
		if (*line == 'B')
			return (true);
		line++;
	}
	return (false);
}

static void	parse_t_map(t_vars *vars, char *line, int *x)
{
	if (*x >= vars->temp_height)
	{
		printf("Error\n");
		free_t_map(vars);
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(line) > vars->temp_width)
	{
		printf("Error\nMap width exceeds defined width\n");
		free_t_map(vars);
		exit(EXIT_FAILURE);
	}
	vars->t_map[*x] = ft_strcpy(vars->t_map[*x], line);
	while (ft_strlen(vars->t_map[*x]) < vars->temp_width - 1)
		vars->t_map[*x] = ft_strcat(vars->t_map[*x], " ");
	vars->t_map[*x][vars->temp_width] = '\0';
	(*x)++;
}
static int ft_empty(char *line)
{
	int i;

	i = 0;
	while ((line[i] <= 13 && line[i] >= 9) || (line[i] == 32))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (1);
	return (0);
}
static void	parse_line(t_vars *vars, char *line, int *x, int *flag)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_texture(vars, line + 3, &vars->texture.north, &flag);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_texture(vars, line + 3, &vars->texture.south, &flag);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_texture(vars, line + 3, &vars->texture.west, &flag);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_texture(vars, line + 3, &vars->texture.east, &flag);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(vars, line + 2, &vars->floor, &flag);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(vars, line + 2, &vars->ceiling, &flag);
	else if (has_special_digits(line))
	{
		*flag = 1;
		parse_t_map(vars, line, x);
	}
	else if (ft_empty(line) == 0)
	{
		printf("Error\n");
		free_t_map(vars);
		exit(EXIT_FAILURE);
	}
	
}

static void	check_duplicate_line(char *line, int i[])
{
	if (ft_strncmp(line, "NO ", 3) == 0 && i[0] == 0)
		i[0] = 1;
	else if (ft_strncmp(line, "SO ", 3) == 0 && i[1] == 0)
		i[1] = 1;
	else if (ft_strncmp(line, "WE ", 3) == 0 && i[2] == 0)
		i[2] = 1;
	else if (ft_strncmp(line, "EA ", 3) == 0 && i[3] == 0)
		i[3] = 1;
	else if (ft_strncmp(line, "F ", 2) == 0 && i[4] == 0)
		i[4] = 1;
	else if (ft_strncmp(line, "C ", 2) == 0 && i[5] == 0)
		i[5] = 1;
	else if ((ft_strncmp(line, "NO ", 3) == 0 && i[0] == 1) \
	|| (ft_strncmp(line, "SO ", 3) == 0 && i[1] == 1) \
	|| (ft_strncmp(line, "WE ", 3) == 0 && i[2] == 1) \
	|| (ft_strncmp(line, "EA ", 3) == 0 && i[3] == 1) \
	|| (ft_strncmp(line, "F ", 2) == 0 && i[4] == 1) \
	|| (ft_strncmp(line, "C ", 2) == 0 && i[5] == 1))
	{
		printf("Error\nDuplicate line\n");
		exit (1);
	}
}

void	parse_map(t_vars *vars, char *file_path, int flag, int flagi)
{
	int		x;
	int		fd;
	char	*line;
	int		i[]= {0, 0, 0, 0, 0, 0};

	fd = open(file_path, O_RDONLY);
	check_fd_error(vars, fd, 1);
	line = get_next_line(fd);
	check_line_error(vars, line, fd, 1);
	x = 0;
	while (line)
	{
		check_duplicate_line(line, i);
		parse_line(vars, line, &x, &flag);
		free(line);
		line = get_next_line(fd);
		if (flag == 1 && line && line[0] == '\n')
			flagi = 1;
		if (flag == 1 && flagi == 1 && line && line[0] != '\n')
		{
			printf("Error\n");
			free(line);
			exit (1);
		}
	}
	close(fd);
}
