#include "cub3d.h"
#include <fcntl.h>
#include <stdlib.h>
#include "./includes/gnl/get_next_line.h"

#include <stdio.h> //todo(apancar):remove

int64_t	ft_strlen_cub(const char *s)
{
	int64_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	get_dimensions(t_game *game, char *av)
{
	int			fd;
	char		**line;
	int64_t		i;

 	fd = open(av, O_RDONLY);
	if (fd < 0)
		return ; //todo(apancar):handle error/free
	line = (char **)malloc(sizeof(char *) * M_HEIGHT);
	if (!line) //close fd
		return ; //todo(apancar):handle error/free
	i = -1;
	while (++i < M_HEIGHT)
	{
		line[i] = get_next_line(fd);
		if (!line[i])
			break ; //todo(apancar):handle error/free
	}
	close(fd);
	game->height = i;
	game->width = ft_strlen_cub(line[0] + 1);
	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

static void	get_map(t_game *game, char *av)
{
	int			fd;
	char		*line;
	int64_t		i;

	fd = open(av, O_RDONLY);
	i = 0;
	while (i < game->height)
	{
		line = get_next_line(fd);
		if (!line)
			return ; //todo(apancar):handle error/free
		game->map[i] = line;
		i++;
	}
	close(fd);
}


void	init_map(t_game *game, char *av)
{
	int64_t	i;

	game->map = (char **)malloc(sizeof(char *) * game->height);
	if (!game->map)
		return ;
	i = 0;
	while (i < game->width)
	{
		game->map[i] = (char *)malloc(sizeof(char) * game->width);
		if (!game->map[i])
		{
			while (i >= 0)
			{
				free(game->map[i]);
				i--;
			}
			free(game->map);
			return ;
		}
		i++;
	}
	get_map(game, av);
}

void init_cam(t_game *game)
{
	game->cam = (t_camera *)malloc(sizeof(t_camera));
	if (!game->cam)
		return ;
	game->cam->posX = 2.0;
	game->cam->posY = 2.0;
	game->cam->dirX = -1.0;
	game->cam->dirY = 0.0;
	game->cam->planeX = 0.0;
	game->cam->planeY = 0.66;
}

void	init_player(t_game *game)
{
	game->player = (t_player *)malloc(sizeof(t_player));
	if (!game->player)
		return ;
	game->player->posX = 2.0;
	game->player->posY = 2.0;
	game->player->dirX = -1.0;
	game->player->dirY = 0.0;
	game->player->planeX = 0.0;
	game->player->planeY = 0.66;
}

void	init_game(t_game *game, char *av)
{
	get_dimensions(game, av);
	init_map(game, av);//todo(apancar):handle error/free
	init_cam(game);//todo(apancar):handle error/free
	init_player(game);//todo(apancar):handle error/free
}