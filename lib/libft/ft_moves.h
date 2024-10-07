/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:18:53 by apancar           #+#    #+#             */
/*   Updated: 2024/10/03 12:21:46 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MOVES_H
# define FT_MOVES_H

# ifdef __linux__

#  include <X11/keysym.h>
#  define ESC_KEY XK_Escape
#  define X_KEY XK_x
#  define Z_KEY XK_z
#  define O_KEY XK_o
#  define Q_KEY XK_q
#  define W_KEY XK_w
#  define E_KEY XK_e
#  define R_KEY XK_r
#  define A_KEY XK_a
#  define S_KEY XK_s
#  define D_KEY XK_d
#  define F_KEY XK_f
#  define P_KEY XK_p
#  define RIGHT_KEY XK_Right
#  define LEFT_KEY XK_Left
#  define UP_KEY XK_Up
#  define DOWN_KEY XK_Down

# else

#  define ESC_KEY 53
#  define X_KEY 7
#  define Z_KEY 6
#  define O_KEY 31
#  define Q_KEY 12
#  define W_KEY 13
#  define E_KEY 14
#  define R_KEY 15
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define F_KEY 3
#  define P_KEY 35
#  define RIGHT_KEY 124
#  define LEFT_KEY 123
#  define UP_KEY 126
#  define DOWN_KEY 125

# endif

typedef enum e_mlx_event
{
	KeyPress = 2,
	KeyRelease = 3,
	ButtonPress = 4,
	ButtonRelease = 5,
	MotionNotify = 6,
	Expose = 12,
	Destroy = 17
}	t_mlx_event;

#endif
