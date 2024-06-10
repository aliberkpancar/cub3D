/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:54:47 by apancar           #+#    #+#             */
/*   Updated: 2024/06/07 12:22:26 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif

# include <stdlib.h>
# include <unistd.h>

char		*get_next_line(int fd);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(const char *s);
// char		*ft_strdup(const char *s1);
char		*extras_for_next(char *temp);
char		*ft_read(int fd, char *temp);
char		*ft_line(char *temp);
char		*ft_strchr(const char *s, int c);

#endif