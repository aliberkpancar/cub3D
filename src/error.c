/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:48 by apancar           #+#    #+#             */
/*   Updated: 2024/10/03 12:15:49 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_fd_error(t_vars *vars, int fd, int flag)
{
	if (fd == -1)
	{
		printf("Error\nOpening file error\n");
		if (flag == 1)
			free_t_map(vars);
		exit(EXIT_FAILURE);
	}
}

void	check_line_error(t_vars *vars, char *line, int fd, int flag)
{
	if (!line)
	{
		printf("Error\nEmpty file\n");
		if (flag == 1)
			free_t_map(vars);
		close(fd);
		exit(EXIT_FAILURE);
	}
}
