/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 06:58:12 by apancar           #+#    #+#             */
/*   Updated: 2024/05/29 08:49:51 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/map_parser.h"
#include "./includes/get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_strlcpy(char *dst, const char *src, int64_t dstsize)
{
	int64_t	i;

	i = 0;
	if (dstsize > 0) {
		while (src[i] && i < dstsize - 1) {
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
}


int64_t parse_all_maps(t_game *game, const char *file_path)
{
	int		fd;
	int64_t	i;
	char	*line;

	if (get_map_size(file_path, game->map) == 1)
		return (perror("Error\nGetting map size."), 1);
	if (allocate_map(game) == 1)
		return (perror("Error\nAllocating map."), 1);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (perror("Error\nOpening map file."), 1);
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
			while (line && line[0] == '1')
			{
				ft_strlcpy(game->map->map[i], line, game->map->cols);
				free (line);
				line = get_next_line(fd);
				i++;
			}
			if (is_valid_map(game) == false)
				return (1);
			if (!line)
				free(line);
			// break; //todo(apancar): remove this break
		}	
		free(line);
	}
	close(fd);
	return (0);
}

