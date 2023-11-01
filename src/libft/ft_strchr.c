/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/30 13:32:22 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int			i;
	const char	*f;

	i = 0;
	f = 0;
	if (!s)
		return (NULL);
	while (*(s + i))
	{
		if (*(s + i) == (unsigned char) c)
		{
			f = (s + i);
			return ((char *) f);
		}
		i++;
	}
	if (c == 0)
		f = (s + ft_strlen(s));
	return ((char *) f);
}
