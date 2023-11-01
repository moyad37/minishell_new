/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/30 13:35:58 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*my;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	my = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!my)
		return (NULL);
	while (s[i] != '\0')
	{
		my[i] = (*f)(i, s[i]);
		i++;
	}
	my[i] = '\0';
	return (my);
}
