#include "cub3d.h"
void	parse_color(char *line, t_color *color)
{
    char	**rgb; 
	int		i;

	rgb = ft_split(line, ',');
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
        printf("Error\nInvalid color format\n");
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

void	parse_texture(char *line, char **texture_path)
{
	char *newline_pos;
	
	newline_pos = ft_strchr(line, '\n');
    if (newline_pos)
		*newline_pos = '\0';
	*texture_path = ft_strdup(line);
	if (*texture_path == NULL)
	{
		perror("Error allocating memory for texture path");
		exit(EXIT_FAILURE);
	}
	*texture_path = ft_strjoin(*texture_path, ".xpm");
}