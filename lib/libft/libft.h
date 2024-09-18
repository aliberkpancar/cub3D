#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include "ftstructs.h"
# include "ftinputs.h"

# define PI 3.14159265358979323846

void		*ft_bzero(void *s, size_t n);
char		*ft_strdup(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strcat(char *dest, const char *src);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_substr(char const *s, int start, int len);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
void		ft_swap_int(int *a, int *b);
char		**ft_split(char const *s, char c);
void		*ft_calloc(size_t nmemb, size_t size);
float		degree_to_radian(float deg);
float		ft_rad_to_deg(float rad);
t_map		ft_map_init(float min_i, float max_i, float min_o, float max_o);
float		ft_normalize(float val, float min, float max);
float		linear_interpolation(float val, float min, float max);
float		ft_map(float val, t_map map);
t_vec		ft_vec_set(float x, float y);
t_vec		ft_vec_sub(t_vec	vec1, t_vec vec2);
t_vec		ft_vec_add(t_vec vec1, t_vec vec2);
t_vec		ft_vec_mul(t_vec vec, float mul);
t_vec		ft_vec_div(t_vec vec, float div);
t_vec		ft_vec_norm(t_vec vec);
t_vec		ft_vec_inversion(t_vec vector);
t_vec		ft_vec_rotate(t_vec vector, float degree);
float		ft_vec_dot(t_vec vec1, t_vec vec2);
float		ft_vec_distance(t_vec point1, t_vec point);
float		ft_vec_mag(t_vec vec);
t_color		ft_set_color(__uint8_t a, __uint8_t r, __uint8_t g, __uint8_t b);
t_color		ft_get_gradient_val(t_color from, t_color to, float value);
t_gradient	ft_set_gradient(t_color from, t_color to);
t_gradient	ft_inv_gradient(t_gradient in);
void		ft_put_pixel(t_image *image, int x, int y, t_color color);

#endif
