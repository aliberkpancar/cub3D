#include "cub3d.h"

void parse_color(t_vars *vars, char *line, t_color *color)
{
	char **rgb;
	int i;

	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		printf("Error\nInvalid color format\n");
		free_t_map(vars);
		exit(EXIT_FAILURE);
	}
	color->red = ft_atoi(rgb[0]);
	color->green = ft_atoi(rgb[1]);
	color->blue = ft_atoi(rgb[2]);
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}

void parse_texture(t_vars *vars, char *line, char **texture_path)
{
	char *newline_pos;
	char *temp;

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
