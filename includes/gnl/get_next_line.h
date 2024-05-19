/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:24:51 by apancar           #+#    #+#             */
/*   Updated: 2023/12/26 14:07:17 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif //BUFFER_SIZE

# include <stdlib.h>
# include <unistd.h>

char		*get_next_line(int fd);
char		*ft_strjoin_gnl(char *s1, char *s2);
size_t		ft_strlen_gnl(const char *s);
char		*ft_strdup_gnl(const char *s1);
char		*extras_for_next(char *temp);
char		*ft_read(int fd, char *temp);
char		*ft_line(char *temp);
char		*ft_strchr_gnl(const char *s, int c);

#endif