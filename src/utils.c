#include "cub3d.h"

static void	update_dimensions(t_vars *vars, char *line, int *row)
{
	int col;

	col = ft_strlen(line);
	if (col > vars->temp_width)
		vars->temp_width = col;
	if (has_0_or_1(line))
		(*row)++;
}

void get_dimensions(t_vars *vars, char *map_path)
{
	int		fd;
	char	*line;
	int		row;

	row = 0;
	fd = open(map_path, O_RDONLY);
	check_fd_error(vars, fd, 0);
	line = get_next_line(fd);
	check_line_error(vars, line, fd, 0);
	vars->temp_width = 0;
	vars->temp_height = 0;
	while (line)
	{
		if (line[0] == '1' || (has_0_or_1(line) && !has_F_and_C(line)))
			update_dimensions(vars, line, &row);
		free(line);
		line = get_next_line(fd);
	}
	vars->temp_height = row;
	close(fd);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	if (!dst || !src)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '\n')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	free_r_t_map(t_vars *head)
{
	int	i;

	i = 0;
	while (head->t_map[i] != NULL)
	{
		free(head->t_map[i]);
		i++;
	}
	free(head->t_map);
	i = 0;
	while (head->r_map[i] != NULL)
	{
		free(head->r_map[i]);
		i++;
	}
	free(head->r_map);
}