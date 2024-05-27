# ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "mlx/mlx.h"

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define MAP_WIDTH 5
# define MAP_HEIGHT 5
# define M_WIDTH 40
# define M_HEIGHT 30

# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define ESC_KEY 53
# define E_KEY 14
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define TILE_SIZE 16
# define TOTAL_RAYS 1280
# define PLAYER_SIZE 5
# define TOTAL_TEXTURES 14
# define SCREENHEIGHT 512
# define SCREENWIDTH 1280
# define MINIMAPWIDTH 7
# define MINIMAPHEIGHT 7

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

typedef int	t_bool;

typedef struct s_camera {
	double	posY;
	double	posX;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
} t_camera;

typedef struct s_ray
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	int64_t		key_w;
	int64_t		key_s;
	int64_t		key_left;
	int64_t		key_right;
	double		camerax;
	double		raydirx;
	double		raydiry;
	double		deltadistx;
	double		deltadisty;
	int64_t		map_x;
	int64_t		map_y;
	int64_t		stepx;
	int64_t		stepy;
	double		sidedistx;
	double		sidedisty;
	int64_t		wall;
	int64_t		side;
	double		perpwalldist;
	int64_t		lineheight;
	int64_t		drawstart;
	int64_t		drawend;
	int64_t		tex_x;
	int64_t		texnum;
	double		texstep;
	double		texpos;
	int64_t		key_a;
	int64_t		key_d;
	int64_t		user_x;
	int64_t		user_y;
}	t_ray;

typedef struct s_player {
	char	*image;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
} t_player;

typedef struct s_map
{
	int64_t	rows;
	int64_t	cols;
	int64_t	map_x;
	int64_t	map_s;
	int64_t	map_y;
	char	**floor;
	char	**ceiling;
	int		floor_color;
	int		ceiling_color;
	char	**map;
	char	**flood_fill;
	char	**wall_textures;
	char	*floor_str;
	char	*ceiling_str;
	char	*map_str;
}				t_map;

typedef struct s_game
{
	int64_t		width;
	int64_t		height;
	void 		*mlx;
	void 		*win;
	void 		*img;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*mlx_img;
	int			*mlx_o_data;
	char		*map_path;
	int			map_fd;
	t_bool		w_pressed;
	t_bool		a_pressed;
	t_bool		s_pressed;
	t_bool		d_pressed;
	t_bool		e_pressed;
	t_bool		is_door_open;
	t_bool		left_pressed;
	t_bool		right_pressed;
	t_bool		left_mouse_pressed;
	t_bool		right_mouse_pressed;
	t_ray		*ray;
	t_camera	*cam;
	t_player	*player;
	t_map		*mini_map;
	t_map		*map;
} 				t_game;


//main.c
void	ft_putstr_fd(char *s, int fd);
int64_t init_map(t_game *game);
int64_t	init_game(t_game *game, const char *file_path);
// void	run_game(t_game *game);
// void	cleanup_game(t_game *game);
void	error_exit(const char *message);
// int64_t	ft_strlen(const char *str);
void	ft_strcpy(char *dest, const char *src);
int64_t init_game(t_game *game, const char *file_path);

# endif
