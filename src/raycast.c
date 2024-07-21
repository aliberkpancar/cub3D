#include "cub3d.h"

static void	hit_vertical_hlpr(t_raycast *ray, t_vec2 start, t_vec2 dir)
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

static t_vec2	hit_vertical(t_vars *vars, t_vec2 start, t_vec2 dir, float *dist)
{
	t_raycast	ray;

	hit_vertical_hlpr(&ray, start, dir);
	while (ray.x >= 0 && ray.x < vars->map.size.x)
	{
		ray.y = ((dir.y / dir.x) * (ray.x - start.x)) + start.y;
		ray.hit.pos = (t_vec2){.x = ray.x, .y = ray.y};
		*dist = ft_vec2_mag(ft_vec2_sub(ray.hit.pos, start));
		if (*dist >= 100)
			return (start);
		if (ray.y >= 0 && ray.y < vars->map.size.y)
			if (vars->map.tiles[(int)(ray.x + ray.offset)
				+ ((int)ray.y * vars->map.size.x)] == '1')
				return (ray.hit.pos);
		ray.x += ray.step;
	}
	return (start);
}

static void	hit_horizontal_hlpr(t_raycast *ray, t_vec2 start, t_vec2 dir)
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

static t_vec2	hit_horizontal(t_vars *cub3d, t_vec2 start, t_vec2 dir, float *dist)
{
	t_raycast	ray;

	hit_horizontal_hlpr(&ray, start, dir);
	while (ray.y > 0 && ray.y < cub3d->map.size.y)
	{
		ray.x = ((dir.x / dir.y) * (ray.y - start.y)) + start.x;
		ray.hit.pos = (t_vec2){.x = ray.x, .y = ray.y};
		*dist = ft_vec2_mag(ft_vec2_sub(ray.hit.pos, start));
		if (*dist >= 100)
			return (start);
		if (ray.x >= 0 && ray.x < cub3d->map.size.x)
			if (cub3d->map.tiles[(int)(ray.x) + (((int)ray.y + ray.offset)
					* cub3d->map.size.x)] == '1')
				return (ray.hit.pos);
		ray.y += ray.step;
	}
	return (start);
}

void	raycast(t_vars *vars, t_vec2 start, t_vec2 dir, t_hit *out)
{
	t_vec2	vertical;
	t_vec2	horizontal;
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