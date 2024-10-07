/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:17:49 by apancar           #+#    #+#             */
/*   Updated: 2024/10/03 12:17:50 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*refill(int fd, char *buffer);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strchr_gnl(char *str, char c);
int		ft_strlen_gnl(char *str);
char	*get_line_str(char *buffer);
char	*cut_line(char *buffer, int len);

#endif