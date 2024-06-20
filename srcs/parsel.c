#include <stdlib.h>
#include <stdio.h>
#include "../includes/cub3d.h"

static char	*ft_strcpy_with_star(t_vars *vars, char *dst, const char *src)
{
	int i;

	if (!dst || !src)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '\n')
	{
		if (src[i] == ' ')
			dst[i] = '*';
		else
			dst[i] = src[i];
		i++;
	}
	while (i < vars->temp_width)
	{
		dst[i] = '*';
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char **allocate_temp_map(t_vars *vars)
{
	int i;

	vars->height = vars->temp_height + 2;
	vars->r_map = (char **) malloc (sizeof(char *) * vars->height);
	if (!vars->r_map)
	{
		perror("Error allocating memory for new map");
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

static char **add_star_lines(t_vars *vars)
{
	int		i;

	vars->r_map = allocate_temp_map(vars);
	if (!vars->r_map)
	{
		perror("Error allocating memory for new map");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < vars->temp_width)
	{
		vars->r_map[0][i] = '*';
		vars->r_map[vars->height - 1][i] = '*';
		i++;
	}
	vars->r_map[0][i] = '\0';
	vars->r_map[vars->height - 1][i] = '\0';
	i = 1;
	while (i < vars->temp_height + 1)
	{
		vars->r_map[i] = ft_strcpy_with_star(vars, vars->r_map[i], vars->temp_map[i - 1]);
		i++;
	}
	return (vars->r_map);
}

void	create_r_map(t_vars *vars)
{	
	vars->r_map = add_star_lines(vars);
	if (!vars->r_map)
	{
		perror("Error creating new map");
		exit(EXIT_FAILURE);
	}
	while (vars->temp_height--)
		free(vars->temp_map[vars->temp_height]);
	free(vars->temp_map);
}
