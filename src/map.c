#include <stdlib.h>
#include <stdio.h>
#include "cub3d.h"

static char	*ft_strcpy_with_b(t_vars *vars, char *dst, const char *src)
{
	int i;

	if (!dst || !src)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '\n')
	{
		if (src[i] == ' ')
			dst[i] = 'B';
		else
			dst[i] = src[i];
		i++;
	}
	while (i < vars->temp_width)
	{
		dst[i] = 'B';
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char **allocate_r_map(t_vars *vars)
{
	int i;

	vars->height = vars->temp_height + 2;
	vars->r_map = (char **) malloc (sizeof(char *) * vars->height);
	if (!vars->r_map)
	{
		printf("Error\nAllocating memory error for new map");
		return (NULL);
	}
	vars->width = vars->temp_width;
	i = 0;
	while (i < vars->height)
	{
		vars->r_map[i] = (char *) malloc (vars->width + 1);
		if (!vars->r_map[i])
		{
			perror("Error allocating memory for new map");
			return (NULL);
		}
		i++;
	}
	return (vars->r_map);
}

static char **add_b_lines(t_vars *vars)
{
	int		i;

	vars->r_map = allocate_r_map(vars);
	if (!vars->r_map)
	{
		printf("Error\nAllocating memory error for new map");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < vars->temp_width)
	{
		vars->r_map[0][i] = 'B';
		vars->r_map[vars->height - 1][i] = 'B';
		i++;
	}
	vars->r_map[0][i] = '\0';
	vars->r_map[vars->height - 1][i] = '\0';
	i = 1;
	while (i < vars->temp_height + 1)
	{
		vars->r_map[i] = ft_strcpy_with_b(vars, vars->r_map[i], vars->t_map[i - 1]);
		i++;
	}
	return (vars->r_map);
}

static t_bool	check_border(t_vars *vars)
{
	int i;
	int j;
	static char valid_chars[] = "1B \n";

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			if (vars->r_map[i][j] == 'B')
			{
				if ((j + 1 < vars->width && !ft_strchr(valid_chars, vars->r_map[i][j + 1])) ||
                    (j - 1 >= 0 && !ft_strchr(valid_chars, vars->r_map[i][j - 1])) ||
                    (i + 1 < vars->height && !ft_strchr(valid_chars, vars->r_map[i + 1][j])) ||
                    (i - 1 >= 0 && !ft_strchr(valid_chars, vars->r_map[i - 1][j])))
					return (printf("Error\nMap is not surrounded by walls\n"), false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

void	create_r_map(t_vars *vars)
{
	vars->r_map = add_b_lines(vars);
	if (!vars->r_map)
	{
		printf("Error\nCreating new map error\n");
		exit(EXIT_FAILURE);
	}
	// while (vars->temp_height--)
	// 	free(vars->t_map[vars->temp_height]);
	// free(vars->t_map);
	if (check_border(vars) == false)
		exit(EXIT_FAILURE);
}
