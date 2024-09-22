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

static void	parse_line(t_vars *vars, char *line, int *x, int *empty_line)
{
	if (line[0] == '\0' || line[0] == '\n' \
	|| ((line[0] == ' ' || line[0] == '\t' || line[0] == '\v' \
	|| line[0] == '\f' || line[0] == '\r') \
	&& !has_special_digits(line)))
		(*empty_line)++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_texture(vars, line + 3, &vars->texture.north);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_texture(vars, line + 3, &vars->texture.south);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_texture(vars, line + 3, &vars->texture.west);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_texture(vars, line + 3, &vars->texture.east);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(vars, line + 2, &vars->floor);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(vars, line + 2, &vars->ceiling);
	else if (has_special_digits(line))
		parse_t_map(vars, line, x);
}

void	parse_map(t_vars *vars, char *file_path)
{
	int		x;
	int		fd;
	char	*line;
	int		empty_line;

	empty_line = 0;
	fd = open(file_path, O_RDONLY);
	check_fd_error(vars, fd, 1);
	line = get_next_line(fd);
	check_line_error(vars, line, fd, 1);
	x = 0;
	while (line)
	{
		parse_line(vars, line, &x, &empty_line);
		if (empty_line >= 3)
		{
			printf("Error\nMultiple maps\n");
			free(line);
			close(fd);
			exit(EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
