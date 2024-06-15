#include "../includes/cub3d.h"
#include "../gnl/get_next_line.h"
#include <fcntl.h>

static char **ft_split(char *s, char c) {
	int count = 0;
	for (int i = 0; s[i]; i++)
		if (s[i] == c)
			count++;
	char **result = malloc(sizeof(char *) * (count + 2));
	if (result == NULL) {
		perror("Error allocating memory for split result");
		exit(EXIT_FAILURE);
	}
	int i = 0;
	int j = 0;
	int start = 0;
	while (s[i]) {
		if (s[i] == c) {
			result[j] = malloc(i - start + 1);
			if (result[j] == NULL) {
				perror("Error allocating memory for split result");
				exit(EXIT_FAILURE);
			}
			memcpy(result[j], s + start, i - start);
			result[j][i - start] = '\0';
			j++;
			start = i + 1;
		}
		i++;
	}
	result[j] = malloc(i - start + 1);
	if (result[j] == NULL) {
		perror("Error allocating memory for split result");
		exit(EXIT_FAILURE);
	}
	memcpy(result[j], s + start, i - start);
	result[j][i - start] = '\0';
	result[j + 1] = NULL;
	return result;
}

void	get_dimensions(t_vars *vars, char *map_path)//check it is not true
{
	int		fd;
	char	*line;
	int		row;
	int		col;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	row = 0;
	line = get_next_line(fd);
	if (!line)
	{
		fprintf(stderr, "Error: Empty file\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
	while (line)
	{
		col = ft_strlen(line);
		if (col > vars->map_width)
			vars->map_width = col;
		row++;
		free(line);
		line = get_next_line(fd);
	}
	vars->map_width += 1;
	vars->map_height = row;
	close(fd);

}

static void parse_color(char *line, t_color *color)
{
    char	**rgb; 
	int		i;

	rgb = ft_split(line, ',');
    if (rgb == NULL || rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL)
	{
        fprintf(stderr, "Error: Invalid color format\n");
        exit(EXIT_FAILURE);
    }
    color->r = atoi(rgb[0]);
    color->g = atoi(rgb[1]);
    color->b = atoi(rgb[2]);
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
    free(rgb);
}

static void parse_texture(char *line, char **texture_path)
{
	char *newline_pos;
	
	newline_pos = strchr(line, '\n');
    if (newline_pos)
		*newline_pos = '\0';
	*texture_path = strdup(line); //ft_strdup(line);
	if (*texture_path == NULL)
	{
		perror("Error allocating memory for texture path");
		exit(EXIT_FAILURE);
	}
}

// static void	ft_strcpy(char *dst, const char *src)
// {
// 	while (*src)
// 		*dst++ = *src++;
// 	*dst = '\0';
// }

// static char	*fill_the_line_with_A(char *line, t_vars *vars)
// {
// 	int i;

// 	i = 0;
// 	while (i < vars->map_width)
// 	{
// 		line[i] = 'A';
// 		i++;
// 	}
// 	line[i] = '\0';
// 	return (line);
// }

void parse_map(char *file_path, t_vars *vars)
{
	int		y;
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	if (!line)
	{
		fprintf(stderr, "Error: Empty file\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
	y = 0;
	while (line)
	{
		if (strncmp(line, "NO ", 3) == 0)
			parse_texture(line + 3, &vars->texture.north);
		else if (strncmp(line, "SO ", 3) == 0)
			parse_texture(line + 3, &vars->texture.south);
		else if (strncmp(line, "WE ", 3) == 0)
			parse_texture(line + 3, &vars->texture.west);
		else if (strncmp(line, "EA ", 3) == 0)
			parse_texture(line + 3, &vars->texture.east);
		else if (strncmp(line, "F ", 2) == 0)
			parse_color(line + 2, &vars->floor);
		else if (strncmp(line, "C ", 2) == 0)
			parse_color(line + 2, &vars->ceiling);
		else if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
        else
		{
            if (y >= vars->map_height)
			{
                fprintf(stderr, "Error: Map exceeds defined height\n");//change to printf
                exit(EXIT_FAILURE);
            }
            if (ft_strlen(line) > vars->map_width)
			{
                fprintf(stderr, "Error: Map width exceeds defined width\n"); //change to printf
                exit(EXIT_FAILURE);
            }
            strncpy(vars->map[y], line, vars->map_width);
			vars->map[y][vars->map_width] = '\0';
            y++;
        }
        free(line);
		line = get_next_line(fd);
    }
	close(fd);
}
