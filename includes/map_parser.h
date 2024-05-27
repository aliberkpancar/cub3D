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
int64_t		fill_the_map(t_game *game, const char *file_path);
bool		is_valid_map(t_game *game);
bool		is_valid_mini_map(char *line);
int64_t		check_map_boundaries(t_game *game);
void		create_mini_map(t_game *game, char *line, int64_t i);

#endif