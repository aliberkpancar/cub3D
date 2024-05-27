/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 07:38:53 by apancar           #+#    #+#             */
/*   Updated: 2024/05/27 14:43:42 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/map_parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "./includes/get_next_line.h"
#include "./includes/cub3d.h"
#include <stdbool.h>


int64_t	get_map_size(const char *file_path, t_map *map)
{
	int		fd;
	int64_t	len;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return(perror("Error opening map file"), 1);
	len = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_strlen_gnl(line) == 0)
		{
			free(line);
			continue ;
		}
		len = ft_strlen_gnl(line);
		if (len > map->cols)
			map->cols = len;
		map->rows++;
		free(line);
	}
	map->rows++;
	close(fd);
	printf("Map size - Rows: %lld, Cols: %lld\n", map->rows, map->cols); // Debugging line
	return (0);
}
// while(1) is ok?

int64_t	allocate_map(t_game *game)
{
	int64_t	i;
	
	game->map->map = (char **) malloc (sizeof(char *) * game->map->rows);
	if (!game->map)
		return (perror("Error allocating memory for map"),1);
	i = 0;
	while (i < game->map->rows)
	{
		game->map->map[i] = (char *) malloc(sizeof(char) * game->map->cols + 1);
		if (!game->map->map[i])
		{
			perror("Error allocating memory for map row");
			while (i > 0)
				free(game->map->map[--i]);
			return (free (game->map->map), 1);
		}
		i++;
	}
	game->mini_map = (t_map *) malloc(sizeof(t_map));
	if (!game->mini_map)
		return (perror("Error allocating memory for mini map"), free(game->map->map), 1);
	return (0);
}

int64_t	fill_the_map(t_game *game, const char *file_path)
{
	int		fd;
	int64_t	i;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return(perror("Error opening map file"), 1);
	i = 0;
	while (i < game->map->rows)
	{
		game->map->map[i] = get_next_line(fd);
		// if (!game->map->map[i])
		// {
		// 	perror("Error reading map file");
		// 	while (i > 0)
		// 		free(game->map->map[--i]);
		// 	free(game->map->map);
		// 	close(fd);
		// 	return (1);
		// }
		i++;
	}
	close(fd);
	return (0);
}

bool	is_valid_map(t_game *game)
{
	int64_t	player_count;
	int64_t	i;
	int64_t	j;

	player_count = 0;
	i = 0;
	while (i < game->map->rows)
	{
		j = 0;
		while (j < game->map->cols)
		{
			if (game->map->map[i][j] == 'N' || game->map->map[i][j] == 'S' || game->map->map[i][j] == 'E'
				|| game->map->map[i][j] == 'W')
				player_count++;
			if (game->map->map[i][j] != '0' && game->map->map[i][j] == '1' && game->map->map[i][j] == '\n' && game->map->map[i][j] != 'N' &&
				game->map->map[i][j] != 'S' && game->map->map[i][j] != 'E' && game->map->map[i][j] != 'W')
				return (ft_putstr_fd("Error\nInvalid character in map\n", 2), false);	
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (ft_putstr_fd("Error\nInvalid number of player start positions\n", 2), false);
	return (true);
}

bool	is_valid_mini_map(char *line)
{
	int64_t	i;

	i = 0;
	while (line[i])
	{
		if (line[0] == '\0' || line[0] == '\n')
		{
			printf("Invalid character in mini map\n");
			return (false);
		}
		if (line[i] != '1' && line[i] != ' ' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (false);
		i++;
	}
	return (true);
}

int64_t	check_map_boundaries(t_game *game)
{
	int64_t	i;
	int64_t	j;

	i = 0;
	j = 0;
	while (j < game->map->cols)
	{
		if (game->map->map[0][j] != '1' || game->map->map[game->map->rows - 1][j] != '1')
			return (ft_putstr_fd("Error\nMap is not enclosed by walls\n", 2), 1);
		j++;
	}
	while (i < game->map->rows)
	{
		if (game->map->map[i][0] != '1' || game->map->map[i][game->map->cols - 1] != '1')
			return (ft_putstr_fd("Error\nMap is not enclosed by walls\n", 2), 1);
		i++;
	}
	return (0);
}

void	create_mini_map(t_game *game, char *line, int64_t i)
{
		printf("==================Mini map: %lld\n", i);
	while (i < game->mini_map->rows)
	{
		if (game->mini_map->map[i])
		{
			game->mini_map->map[i] = ft_strdup_gnl(line);
			if (!game->mini_map->map[i])
			{
				perror("Error allocating memory for mini map row");
				while (i > 0)
					free(game->mini_map->map[--i]);
				free(game->mini_map->map);
				return ;
			}
			break ;
		}
		i++;
	}
}
