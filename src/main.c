/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 06:54:57 by apancar           #+#    #+#             */
/*   Updated: 2024/05/29 08:14:00 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"
#include <unistd.h>
#include "./includes/cub3d.h"
#include "./includes/map_parser.h"
#include "./includes/get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen_gnl(s));
}

int64_t init_map(t_game *game)
{
	game->map = (t_map *)malloc(sizeof(t_map));
	if (!game->map)
		return (1);
	game->map->rows = 0;
	game->map->mini_rows = 0;
	game->map->cols = 0;
	game->map->ceiling_color = 0;
	game->map->ceiling_color = 0;
	game->map->floor = NULL;
	game->map->ceiling = NULL;
	game->map->map = NULL;
	game->map->flood_fill = NULL;
	game->map->wall_textures = NULL;
	game->map->floor_str = NULL;
	game->map->ceiling_str = NULL;
	game->map->map_str = NULL;
	return (0);
}

int64_t init_game(t_game *game, const char *file_path)
{
	if (init_map(game) == 1)
		return(1);
	if (parse_all_maps(game, file_path) == 1)
		return (1);
	return (0);
}

int	main(int ac, char *av[])
{
	t_game	game;
	
	if (ac != 2)
		return (ft_putstr_fd("Invalid number of arguments.\n", 2), 1);
	if (init_game(&game, av[1]) == 1)
		return (ft_putstr_fd("Failed to initialize the game.\n", 2), 1);
	int64_t i = 0;
	while (i < game.map->mini_rows)
		printf("%s\n", game.map->map[i++]);
	// run_game(&game);
	// cleanup_game(&game);
	return (0);
}
