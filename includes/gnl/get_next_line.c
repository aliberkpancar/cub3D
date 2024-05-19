/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:53:38 by apancar           #+#    #+#             */
/*   Updated: 2024/01/20 13:47:21 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *temp)
{
	char	*buff;
	int		nbr_bytes;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE) + 1);
	if (!buff)
		return (NULL);
	nbr_bytes = 1;
	while (!ft_strchr_gnl(temp, '\n') && nbr_bytes != 0)
	{
		nbr_bytes = read(fd, buff, BUFFER_SIZE);
		if (nbr_bytes == -1)
		{
			free(buff);
			free(temp);
			return (NULL);
		}
		buff[nbr_bytes] = '\0';
		temp = ft_strjoin_gnl(temp, buff);
	}
	return (free(buff), temp);
}

char	*ft_line(char *temp)
{
	char	*line;
	int		i;

	i = 0;
	if (!temp[i])
		return (NULL);
	while (temp[i] != '\n' && temp[i] != '\0')
		i++;
	if (temp[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (temp[i] != '\n' && temp[i] != '\0')
	{
		line[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*extras_for_next(char *temp)
{
	char	*next;
	size_t	i;
	size_t	j;

	if (!temp)
		return (NULL);
	i = 0;
	while (temp[i] != '\n' && temp[i] != '\0')
		i++;
	if (temp[i] == '\0')
		return (free(temp), NULL);
	if (temp[i] == '\n')
		i++;
	next = (char *)malloc(sizeof(char) * (ft_strlen_gnl(temp) - i) + 1);
	if (!next)
		return (NULL);
	j = 0;
	while (temp[i])
		next[j++] = temp[i++];
	next[j] = '\0';
	return (free(temp), next);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = ft_read(fd, temp);
	if (!temp)
		return (NULL);
	line = ft_line(temp);
	temp = extras_for_next(temp);
	return (line);
}
