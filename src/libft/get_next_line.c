/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/09/15 13:58:03 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_save_modifid_and_send(int fd, char *temp);
char	*rm_line(char *temp);


char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = read_save_modifid_and_send(fd, temp);
	if (!temp)
		return (NULL);
	line = send_line_gnl(temp);
	temp = rm_line(temp);
	return (line);
}

char	*rm_line(char *temp)
{
	char	*new_temp;
	int		hin;
	int		i;

	i = 0;
	hin = 0;
	hin = hin_bis_cut_gnl(temp);
	if (!temp[hin])
	{
		free(temp);
		return (NULL);
	}
	hin++;
	new_temp = malloc_and_check((ft_strlen_gnl(temp + hin) + 1), sizeof(char));
	while (temp[hin] != '\0')
	{
		new_temp[i] = temp[hin];
		i++;
		hin++;
	}
	new_temp[i] = 0;
	free(temp);
	return (new_temp);
}

void	ft_bzero_gnl(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

char	*malloc_and_check(size_t count, size_t size)
{
	char	*result;

	result = malloc(count * size);
	if (!result)
		return (NULL);
	ft_bzero_gnl(result, (size * count));
	return (result);
}

char	*read_save_modifid_and_send(int fd, char *temp)
{
	int		read_check;
	char	*buff;

	buff = malloc_and_check((BUFFER_SIZE + 1), 1);
	read_check = 1;
	while (read_check > 0)
	{
		read_check = read(fd, buff, BUFFER_SIZE);
		if (read_check == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_check] = '\0';
		temp = ft_strjoin_gnl(temp, buff);
		if (ft_strchr_gnl(buff, '\n'))
			break ;
	}
	free(buff);
	return (temp);
}
