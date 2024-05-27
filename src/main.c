/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 06:54:57 by apancar           #+#    #+#             */
/*   Updated: 2024/05/27 12:29:58 by apancar          ###   ########.fr       */
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
		return (perror("Error allocating memory for map struct"), 1);
	game->map->rows = 0;
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
        return(ft_putstr_fd("Error\nFailed to initialize the game\n", 2), 1);
	if (parse_map(game, file_path) == 1)
		return (free(game->map), 1);
	return (0);
}

int	main(int ac, char *av[])
{
	t_game	game;
	
	if (ac != 2)
		return (ft_putstr_fd("Error\nInvalid number of arguments\n", 2), 1);
	if (init_game(&game, av[1]) == -1)
		return (ft_putstr_fd("Error\nFailed to initialize the game\n", 2), 1);
	int64_t i = 0;
	while (i < game.mini_map->rows)
		printf("%s\n", game.mini_map->map[i++]);
	// run_game(&game);
	// cleanup_game(&game);
	return (0);
}
