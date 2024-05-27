/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 06:58:12 by apancar           #+#    #+#             */
/*   Updated: 2024/05/27 14:42:31 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/map_parser.h"
#include "./includes/get_next_line.h"
#include <stdlib.h>
#include <stdio.h>


int64_t	parse_map(t_game *game, const char *file_path)
{
	if (get_map_size(file_path, game->map) == 1)
		return (1);
	if (allocate_map(game) == 1)
		return (1);
	if (fill_the_map(game, file_path) == 1)
		return (1);
	// if (!is_valid_map(game))
	// 	return (1);
	// if (!check_map_boundaries(game))
	// 	return (1);
	parse_all_maps(game, file_path);
	return (0);
}

int64_t parse_all_maps(t_game *game, const char *file_path)
{
	int		fd;
	int64_t	i;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening map file"), 1);
	while ((line = get_next_line(fd)))
	{
		// if (line[0] == 'R')
		// 	if (!parse_resolution(line, game))
		// 		return (free(line), close(fd), 1);
		// else if (line[0] == 'F')
		// 	if (!parse_color(line, game->map->floor_color))
		// 		return (free(line), close(fd), 1);
		// else if (line[0] == 'C')
		// 	if (!parse_color(line, game->map->ceiling_color))
		// 		return (free(line), close(fd), 1);
		// todo(apancar): else if will be added later
		if (line[0] == '1')
		{
			i = 0;
			
			while (line && !is_valid_mini_map(line))
			{
				create_mini_map(game, line, i);
				// printf("Mini map: %s\n", game->mini_map->map[i]);
				// printf("Mini map: %lld\n", game->mini_map->rows);
				free(line);
				line = get_next_line(fd);
				i++;
			}
			free(line);
			close(fd);
			return (get_map_size(file_path, game->mini_map) || allocate_map(game) || fill_the_map(game, file_path));
		}	
		free(line);
	}
	close(fd);
	return (0);
}

