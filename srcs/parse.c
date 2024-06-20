#include "../includes/cub3d.h"
#include "../gnl/get_next_line.h"
#include <fcntl.h>
#include <stdbool.h>

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

static bool has_0_or_1(char *line)
{
	while (*line)
	{
		if (*line == '0' || *line == '1')
			return (true);
		line++;
	}
	return (false);
}

static bool has_F_and_C(char *line)
{
	while (*line)
	{
		if (*line == 'F' || *line == 'C')
			return (true);
		line++;
	}
	return (false);
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
		if (line[0] == '1' || (has_0_or_1(line) && !has_F_and_C(line)))
		{
			col = ft_strlen(line);
			if (col > vars->temp_width)
				vars->temp_width = col;
			row++;
			free(line);
		}
		line = get_next_line(fd);
	}
	vars->temp_width += 1;
	vars->temp_height = row;
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
    color->r = atoi(rgb[0]);//write ft_atoi
    color->g = atoi(rgb[1]);//write ft_atoi
    color->b = atoi(rgb[2]);//write ft_atoi
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
    free(rgb);
}

static void parse_texture(char *line, char **texture_path)
{
	char *newline_pos;
	
	newline_pos = ft_strchr(line, '\n');
    if (newline_pos)
		*newline_pos = '\0';
	*texture_path = strdup(line); //ft_strdup(line);
	if (*texture_path == NULL)
	{
		perror("Error allocating memory for texture path");
		exit(EXIT_FAILURE);
	}
}

static char	*ft_strcpy(char *dst, const char *src)
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

void parse_map(char *file_path, t_vars *vars)
{
	int		x;
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
	x = 0;
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
		else if (!has_0_or_1(line))
		{
			line = get_next_line(fd);
			continue ;
		}
		else
		{
			if (x >= vars->temp_height)
			{
				printf("Error: Map exceeds defined height\n");
				exit(EXIT_FAILURE);
			}
			if (ft_strlen(line) > vars->temp_width)
			{
				printf("Error: Map width exceeds defined width\n");
				exit(EXIT_FAILURE);
			}
			vars->temp_map[x] = ft_strcpy(vars->temp_map[x], line);
			vars->temp_map[x][vars->temp_width] = '\0';
			x++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
