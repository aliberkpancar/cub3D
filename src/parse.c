#include "cub3d.h"
#include <stdbool.h>

t_bool	has_0_or_1(char *line)
{
	while (*line)
	{
		if (*line == '0' || *line == '1')
			return (true);
		line++;
	}
	return (false);
}

t_bool	has_F_and_C(char *line)
{
	while (*line)
	{
		if (*line == 'F' || *line == 'C')
			return (true);
		line++;
	}
	return (false);
}

static void	parse_t_map(t_vars *vars, char *line, int *x)
{
	if (*x >= vars->temp_height)
	{
		printf("Error\nMap exceeds defined height\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(line) > vars->temp_width)
	{
		printf("Error\nMap width exceeds defined width\n");
		exit(EXIT_FAILURE);
	}
	vars->t_map[*x] = ft_strcpy(vars->t_map[*x], line);
	while (ft_strlen(vars->t_map[*x]) < vars->temp_width - 1)
		vars->t_map[*x] = ft_strcat(vars->t_map[*x], " ");
	vars->t_map[*x][vars->temp_width] = '\0';
	(*x)++;
}

static void	parse_line(t_vars *vars, char *line, int *x)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_texture(line + 3, &vars->texture.north);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_texture(line + 3, &vars->texture.south);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_texture(line + 3, &vars->texture.west);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_texture(line + 3, &vars->texture.east);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(line + 2, &vars->floor);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(line + 2, &vars->ceiling);
	else if (has_0_or_1(line))
		parse_t_map(vars, line, x);
}

void	parse_map(t_vars *vars, char *file_path)
{
	int		x;
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	check_fd_error(fd);
	line = get_next_line(fd);
	check_line_error(line, fd);
	x = 0;
	while (line)
	{
		parse_line(vars, line, &x);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
