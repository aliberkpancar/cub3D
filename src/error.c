#include "cub3d.h"

void	check_fd_error(t_vars *vars, int fd, int flag)
{
	if (fd == -1)
	{
		printf("Error\nOpening file error\n");
		if (flag == 1)
			free_t_map(vars);
		exit(EXIT_FAILURE);
	}
}

void	check_line_error(t_vars *vars, char *line, int fd, int flag)
{
	if (!line)
	{
		printf("Error\nEmpty file\n");
		if (flag == 1)
			free_t_map(vars);
		close(fd);
		exit(EXIT_FAILURE);
	}
}
