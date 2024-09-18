#include "cub3d.h"

static void	init_vertical_ray(t_raycast *ray, t_vec start, t_vec dir)
{
	if (dir.x < 0)
	{
		ray->x = (int)start.x;
		ray->step = -1;
		ray->offset = -1;
	}
	else
	{
		ray->x = (int)start.x + 1;
		ray->step = 1;
		ray->offset = 0;
	}
}

static t_vec	hit_vertical(t_vars *vars, t_vec start, t_vec dir, float *dist)
{
	t_raycast	ray;

	init_vertical_ray(&ray, start, dir);
	while (ray.x >= 0 && ray.x < vars->map.size.x)
	{
		ray.y = ((dir.y / dir.x) * (ray.x - start.x)) + start.y;
		ray.hit.pos = (t_vec){.x = ray.x, .y = ray.y};
		*dist = ft_vec_mag(ft_vec_sub(ray.hit.pos, start));
		if (*dist >= 100)
			break ;
		if (ray.y >= 0 && ray.y < vars->map.size.y && ray.x
			+ ray.offset >= 0 && ray.x + ray.offset < vars->map.size.x)
			if (vars->map.tiles[(int)(ray.x + ray.offset)
				+ ((int)ray.y * vars->map.size.x)] == '1')
				return (ray.hit.pos);
		ray.x += ray.step;
	}
	return ((t_vec){.x = 0, .y = 0});
}

static void	init_horizontal_ray(t_raycast *ray, t_vec start, t_vec dir)
{
	if (dir.y < 0)
	{
		ray->y = (int)start.y;
		ray->step = -1;
		ray->offset = -1;
	}
	else
	{
		ray->y = (int)start.y + 1;
		ray->step = 1;
		ray->offset = 0;
	}
}

static t_vec	hit_horizontal(t_vars *cub3d, t_vec start, t_vec dir,
	float *dist)
{
	t_raycast	ray;

	init_horizontal_ray(&ray, start, dir);
	while (ray.y >= 0 && ray.y < cub3d->map.size.y)
	{
		ray.x = ((dir.x / dir.y) * (ray.y - start.y)) + start.x;
		ray.hit.pos = (t_vec){.x = ray.x, .y = ray.y};
		*dist = ft_vec_mag(ft_vec_sub(ray.hit.pos, start));
		if (*dist >= 100)
			break ;
		if (ray.x >= 0 && ray.x < cub3d->map.size.x && ray.y
			+ ray.offset >= 0 && ray.y + ray.offset < cub3d->map.size.y)
			if (cub3d->map.tiles[(int)(ray.x) + (((int)ray.y + ray.offset)
					* cub3d->map.size.x)] == '1')
				return (ray.hit.pos);
		ray.y += ray.step;
	}
	return ((t_vec){.x = 0, .y = 0});
}

void	raycast(t_vars *vars, t_vec start, t_vec dir, t_hit *out)
{
	t_vec	vertical;
	t_vec	horizontal;
	float	dist_vertical;
	float	dist_horizontal;

	dist_vertical = 0;
	dist_horizontal = 0;
	vertical = hit_vertical(vars, start, dir, &dist_vertical);
	horizontal = hit_horizontal(vars, start, dir, &dist_horizontal);
	if (dist_horizontal <= dist_vertical)
	{
		out->pos = horizontal;
		if ((start.y - horizontal.y) < 0)
			out->face = north;
		else
			out->face = south;
	}
	else
	{
		out->pos = vertical;
		if ((start.x - vertical.x) < 0)
			out->face = west;
		else
			out->face = east;
	}
}
