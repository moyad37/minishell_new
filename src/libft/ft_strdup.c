/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/30 13:33:15 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*my;
	int		i;
	int		size;

	size = 0;
	i = 0;
	while (s[size])
	{
		size++;
	}
	my = malloc(sizeof(char) * (size + 1));
	if (!my)
		return (NULL);
	while (s[i])
	{
		my[i] = s[i];
		i++;
	}
	my[i] = '\0';
	return (my);
}
