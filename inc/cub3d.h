/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:14:55 by apancar           #+#    #+#             */
/*   Updated: 2024/11/07 12:33:45 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

struct s_mini_temp
{
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
};

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
	float	move_speed;
	float	camera_speed;
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
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

typedef struct s_moves
{
	t_bool	esc_key;
	t_bool	right_key;
	t_bool	left_key;
	t_bool	w_key;
	t_bool	a_key;
	t_bool	s_key;
	t_bool	d_key;
}	t_moves;

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}			t_texture;

typedef struct s_raycast
{
	float	x;
	float	y;
	int		offset;
	int		step;
	float	dist;
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
	float		ray_angle[WIDTH];
	double		delta_time;
	int			num_of_rays;
	char		**r_map;
	char		**t_map;
	t_mlx		mlx;
	t_tile_map	map;
	t_player	player;
	t_moves		moves;
	t_image		tex_north;
	t_image		tex_west;
	t_image		tex_south;
	t_image		tex_east;
	t_hit		collisions[WIDTH];
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
void	transform_texture(t_image *tex);
void	flip_texture(t_image *tex);
float	calculate_texture_y(t_image *tex, float i, float height);
void	setup_texture_rendering(int *i, float *tex_y,
			float *full_height, float *line_height);
t_color	*fetch_texture_data(t_image *tex, float tex_x);
int		game(void *param);
void	ft_sketch_line(t_mlx *dt, t_vec pt1, t_vec pt2, t_color color);
void	draw_background(t_vars *vars);
void	draw_walls(t_vars *vars);
int		key_press_handler(int keycode, t_vars *vars);
int		key_release_handler(int keycode, t_vars *vars);
void	player_movement(t_vars *vars, t_vec dir);
void	player_camera(t_vars *vars, t_bool rotate_dir);
void	parse_color(t_vars *vars, char *line, t_color *color, int **flag);
void	parse_texture(t_vars *vars, char *line,
			char **texture_path, int **flag);
void	parse_map(t_vars *vars, char *file_path, int flag, int flagi);
void	get_dimensions(t_vars *vars, char *map_path, int row);
void	create_r_map(t_vars *vars);
void	check_r_map(t_vars *vars);
void	get_player_positions(t_vars *vars);
void	check_fd_error(t_vars *vars, int fd, int flag);
void	check_line_error(t_vars *vars, char *line, int fd, int flag);
t_bool	has_special_digits(char *line);
t_bool	has_special_chars(char *line);
void	draw_minimap(t_vars *vars);
char	*ft_strcpy(char *dst, const char *src);
void	free_t_map(t_vars *vars);
void	free_r_map(t_vars *vars);
void	free_textures(t_vars *vars);
void	init_player(t_vars *vars);
void	init_textures(t_vars *vars);
void	init_win(t_vars *vars);
void	ft_draw_circle(t_mlx *mlx, int *center, int radius, int color);
void	ft_draw_rect(t_mlx *mlx, int x, int y, int color);
void	ft_sketch_line(t_mlx *mlx, t_vec pt1, t_vec pt2, t_color color);
t_vec	set_vals(float x, float y);
void	init_vertical_ray(t_raycast *ray, t_vec start, t_vec dir);
t_vec	hit_vertical(t_vars *vars, t_vec start, t_vec dir, float *dist);
void	init_horizontal_ray(t_raycast *ray, t_vec start, t_vec dir);
t_vec	hit_horizontal(t_vars *cub3d, t_vec start, t_vec dir, float *dist);
void	free_rgb(char **rgb, int flag);
void	dispose_t_map(t_vars *vars, int flag);
void	check_flag(t_vars *vars, int ***flag);
void	free_all(t_vars *vars, int flag);
t_bool	has_special_b(char *line);

#endif
