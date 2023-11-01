/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/30 13:34:28 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	ft_strcpy(char *dest, const char *src);

// static void	ft_strcpy(char *dest, const char *src)
// {
// 	int		i;
// 	size_t	dest_len;

// 	i = 0;
// 	dest_len = ft_strlen(dest);
// 	if (!src)
// 		return ;
// 	while (*(src + i))
// 	{
// 		*(dest + dest_len + i) = *(src + i);
// 		i++;
// 	}
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*finalstr;

// 	finalstr = ft_calloc(1, ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (!finalstr)
// 		return (NULL);
// 	ft_strcpy(finalstr, s1);
// 	ft_strcpy(finalstr, s2);
// 	*(finalstr + ft_strlen(s1) + ft_strlen(s2)) = '\0';
// 	return (finalstr);
// }


char	*first_part(char *p, char const *s1)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	return (p);
}

char	*secund_part(char *p, char const *s2, int i)
{
	int	z;

	z = 0;
	while (s2[z] != '\0')
	{
		p[i] = s2[z];
		i++;
		z++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!p)
		return (NULL);
	p = first_part(p, s1);
	p = secund_part(p, s2, i);
	return (p);
}
