#ifndef CUB3D_H
# define CUB3D_H

# include <time.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "mlx.h"
# include "get_next_line_bonus.h"
# include "libft.h"

# define HEIGHT			1024
# define WIDTH			1280
# define PLAYER_RAD		6
# define PLAYER_SIZE	0.2
# define MINIMAP_SCALE 0.2
# define MINIMAP_WIDTH 200
# define MINIMAP_HEIGHT 200
# define NULL_VEC (t_vec){.x = 0, .y = 0}

typedef union u_vec2i
{
	struct
	{
		int	x;
		int	y;
	};
	int	data[2];
}	t_veci;

typedef struct s_tile_map
{
	char	*tiles;
	t_veci	size;
}	t_tile_map;

typedef struct s_player
{
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
	float	move_speed;
	float	camera_speed;
}	t_player;

typedef enum e_face
{
	north,
	west,
	south,
	east
}	t_face;

typedef struct s_hit
{
	t_vec	pos;
	t_face	face;
}	t_hit;

typedef struct s_input
{
	t_bool	w_key;
	t_bool	a_key;
	t_bool	s_key;
	t_bool	d_key;
	t_bool	right_key;
	t_bool	left_key;
	t_bool	esc_key;
}	t_input;

typedef struct s_logger
{
	FILE	*frame_log;
}	t_logger;

typedef struct	s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		north_width;
	int		north_height;
	int		south_width;
	int		south_height;
	int		west_width;
	int		west_height;
	int		east_width;
	int		east_height;
}			t_texture;

typedef struct s_raycast
{
	float	x;
	float	y;
	int		offset;
	int		step;
	float	dist;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
	t_hit	hit;
}			t_raycast;

typedef struct s_vars
{
	int			temp_width;
	int			temp_height;
	int			width;
	int			height;
	int			player_count;
	float		collision_degree[WIDTH];
	double		delta_time;
	int			collission_count;
	char 		**r_map;
	char		**t_map;
	t_mlx		mlx;
	t_tile_map	map;
	t_player	player;
	t_input		inputs;
	t_image		tex_north;
	t_image		tex_west;
	t_image		tex_south;
	t_image		tex_east;
	t_hit		collisions[WIDTH];
	t_logger	log;
	t_texture	texture;
	t_color		ceiling;
	t_color		floor;
	t_raycast	ray;
}				t_vars;

struct s_draw_hlpr
{
	t_vars	*vars;
	t_image	*tex;
	float	line_height;
	float	tex_x;
	int		index;
};

void	raycast(t_vars *vars, t_vec start, t_vec dir, t_hit *out);
void	init_game(t_vars *vars, char *map);
void	rotate_index(t_image *tex);
void	mirror_tex(t_image *tex);
float	get_tex_y(t_image *tex, float i, float height);
void	draw_tex_helper(int *i, float *tex_y,
	float *full_height, float *line_height);
t_color	*get_tex_data(t_image *tex, float tex_x);
int		game(void *param);
void	ft_draw_line(t_mlx *dt, t_vec pt1, t_vec pt2, t_color color);
void	draw_background(t_vars *vars);
void	draw_walls(t_vars *vars);
int		key_press_handler(int keycode, t_vars *vars);
int		key_release_handler(int keycode, t_vars *vars);
void	player_movement(t_vars *vars, t_vec dir);
void	player_camera(t_vars *vars, t_bool rotate_dir);
void	parse_color(t_vars *vars, char *line, t_color *color);
void	parse_texture(t_vars *vars, char *line, char **texture_path);
void	parse_map(t_vars *vars, char *file_path);
void	get_dimensions(t_vars *vars, char *map_path);
void	create_r_map(t_vars *vars);
void	check_r_map(t_vars *vars);
void	get_player_positions(t_vars *vars);
void	check_fd_error(t_vars *vars, int fd, int flag);
void	check_line_error(t_vars *vars, char *line, int fd, int flag);
t_bool	has_0_or_1(char *line);
t_bool	has_F_and_C(char *line);
void	draw_minimap(t_vars *vars);
char	*ft_strcpy(char *dst, const char *src);
void	free_t_map(t_vars *vars);
void	free_r_map(t_vars *vars);
void	free_all(t_vars *vars);
void	destroy_window(t_vars *vars);

#endif
