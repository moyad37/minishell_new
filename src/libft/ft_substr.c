/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:24:22 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/30 13:39:33 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*my;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		start = ft_strlen(s);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	my = malloc(sizeof(char) * (len + 1));
	if (!my)
		return (0);
	ft_strlcpy(my, s + start, len + 1);
	return (my);
}
