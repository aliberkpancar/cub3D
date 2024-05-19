/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:25:06 by apancar           #+#    #+#             */
/*   Updated: 2023/12/26 14:09:12 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *temp, char *buff)
{
	char	*str;
	size_t	str_len;
	size_t	i;
	size_t	j;

	if (!temp)
	{
		temp = malloc(sizeof(char) * 1);
		temp[0] = '\0';
	}
	str_len = ft_strlen_gnl(temp) + ft_strlen_gnl(buff);
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (temp[++i])
		str[i] = temp[i];
	j = 0;
	while (buff[j])
		str[i++] = buff[j++];
	str[i] = '\0';
	return (free(temp), str);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}
