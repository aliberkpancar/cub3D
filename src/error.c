#include "cub3d.h"

void	check_fd_error(int fd)
{
	if (fd == -1)
	{
		printf("Error\nOpening file error\n");
		exit(EXIT_FAILURE);
	}
}

void	check_line_error(char *line, int fd)
{
	if (!line)
	{
		printf("Error\nEmpty file\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
}

// void	allocation_error(void)
// {
// 	printf("Error\nAllocation error\n");
// 	exit(EXIT_FAILURE);
// }
