#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include "./includes/cub3d.h"
#include <stdbool.h>


// map_parser.c
int64_t		parse_map(t_game *game, const char *file_path);
int64_t		parse_all_maps(t_game *game, const char *file_path);

// map.c
int64_t		get_map_size(const char *file_path, t_map *map);
int64_t		allocate_map(t_game *game);
bool		is_valid_map(t_game *game);
int64_t		check_map_boundaries(t_game *game);

#endif