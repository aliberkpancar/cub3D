#ifndef CUB3D_H
#define CUB3D_H

#include "../mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h> //delete
#include "../gnl/get_next_line.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define MOVE_SPEED 0.1
#define ROTATE_SPEED 0.05

#define MAP_WIDTH 42
#define MAP_HEIGHT 42

typedef struct	s_player
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}			t_player;

typedef struct	s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	void	*north_image;
	void	*south_image;
	void	*west_image;
	void	*east_image;
	int		north_width;
	int		north_height;
	int		south_width;
	int		south_height;
	int		west_width;
	int		west_height;
	int		east_width;
	int		east_height;
}			t_texture;

typedef struct	s_image
{
	void	*image;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	struct s_texture	texture;
}			t_image;


typedef struct	s_ray
{
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}			t_ray;

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

// check if rgb values are between 0 and 255
// check if there are 3 values
// check endianess

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
    double  	dir_x;
	double		dir_y;
	double  	pos_x;
	double		pos_y;
    double  	plane_x;
	double		plane_y;
	int			map_width;
	int			map_height;
	char		**map;
	t_ray		ray;
	t_color		floor;
	t_image 	image;
	t_player	player;
	t_color		ceiling;
	t_texture	textures;
}				t_vars;

// Function prototypes
int		handle_input(int keycode, t_vars *vars);
void	parse_map(char *file_path, t_vars *vars);
void	rotate_player(t_player *player, float angle);
void	move_player(t_vars *vars, float move_x, float move_y);
void	render_scene(t_vars *vars);
int     main_loop(t_vars *vars);
void	get_dimensions(t_vars *vars, char *map_path);
void	textre_calculation(t_vars *vars, int x);
void	texture_init(t_vars *vars);
void	my_mlx_pixel_put_int(t_image *image, int x, int y, int color);

#endif