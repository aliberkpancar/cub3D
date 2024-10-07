/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alize.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:26 by apancar           #+#    #+#             */
/*   Updated: 2024/10/03 12:15:27 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_win(t_vars *vars)
{
	if (vars->mlx.mlx == NULL)
	{
		free_t_map(vars);
		free_r_map(vars);
		free_textures(vars);
		exit(EXIT_FAILURE);
	}
	vars->mlx.win.height = HEIGHT;
	vars->mlx.win.width = WIDTH;
	vars->mlx.win.win = mlx_new_window(vars->mlx.mlx,
			WIDTH, HEIGHT, "cub3D");
	if (vars->mlx.win.win == NULL)
	{
		free_t_map(vars);
		free_r_map(vars);
		free_textures(vars);
		exit(EXIT_FAILURE);
	}
	vars->mlx.image.image = mlx_new_image(vars->mlx.mlx,
			vars->mlx.win.width, vars->mlx.win.height);
	vars->mlx.image.data = (t_color *)mlx_get_data_addr(vars->mlx.image.image,
			&vars->mlx.image.bits_per_pixel,
			&vars->mlx.image.size_line, &vars->mlx.image.endian);
	vars->mlx.image.size_line /= 4;
}

static void	init_tex(t_vars *vars, t_image *tex, char *path)
{
	tex->line_count = vars->height - 2;
	tex->size_line = vars->width - 1;
	tex->image = mlx_xpm_file_to_image(vars->mlx.mlx, path,
			&tex->size_line, &tex->line_count);
	if (!tex->image)
	{
		printf("Error\n");
		free_t_map(vars);
		free_r_map(vars);
		free_textures(vars);
		exit(EXIT_FAILURE);
	}
	tex->data = (t_color *)mlx_get_data_addr(tex->image, &tex->bits_per_pixel,
			&tex->size_line, &tex->endian);
	if (!tex->data)
	{
		printf("Error\n");
		free_t_map(vars);
		free_r_map(vars);
		free_textures(vars);
		exit(EXIT_FAILURE);
	}
	tex->size_line /= (tex->bits_per_pixel / 8);
	transform_texture(tex);
}

void	init_textures(t_vars *vars)
{
	init_tex(vars, &vars->tex_south, vars->texture.north);
	init_tex(vars, &vars->tex_west, vars->texture.south);
	init_tex(vars, &vars->tex_north, vars->texture.west);
	init_tex(vars, &vars->tex_east, vars->texture.east);
	flip_texture(&vars->tex_north);
	flip_texture(&vars->tex_east);
}

void	init_player(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->temp_height)
	{
		j = 0;
		while (j < vars->temp_width)
		{
			if (vars->t_map[i][j] == 'N' || vars->t_map[i][j] == 'S' ||
				vars->t_map[i][j] == 'W' || vars->t_map[i][j] == 'E')
			{
				if (vars->t_map[i][j] == 'N')
					vars->player.dir = (t_vec){.x = 0.0, .y = -1.0};
				else if (vars->t_map[i][j] == 'S')
					vars->player.dir = (t_vec){.x = 0.0, .y = 1.0};
				else if (vars->t_map[i][j] == 'W')
					vars->player.dir = (t_vec){.x = -1.0, .y = 0.0};
				else if (vars->t_map[i][j] == 'E')
					vars->player.dir = (t_vec){.x = 1.0, .y = 0.0};
			}
			j++;
		}
		i++;
	}
}
