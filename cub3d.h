# ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define MAP_WIDTH 5
# define MAP_HEIGHT 3
# define M_WIDTH 40
# define M_HEIGHT 30

typedef struct s_camera {
	double	posY;
	double	posX;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
} t_camera;

typedef struct s_player {
	char	*image;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
} t_player;

typedef struct s_game {
	char	**map;
	int64_t	width;
	int64_t	height;
	void 	*mlx;
	void 	*win;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	t_camera	*cam;
	t_player	*player;
} t_game;

void	move_forward(t_camera *cam, char **map);
void	move_backward(t_camera *cam, char **map);
void	rotate_left(t_camera *cam);
void	rotate_right(t_camera *cam);
int		key_press(t_game *game, int keycode);
//init
void	init_game(t_game *game, char *av);
void	init_map(t_game *game, char *av);
//utils
int64_t	ft_strlen_cub(const char *s);

# endif
