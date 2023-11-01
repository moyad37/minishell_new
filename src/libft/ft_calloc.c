/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/09/15 13:38:10 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*p;

	if (nitems == __SIZE_MAX__ || size == __SIZE_MAX__)
		return (NULL);
	if (nitems == 0 || size == 0)
	{
		nitems = 1;
		size = 1;
	}
	p = malloc(nitems * size);
	if (!p)
		return (NULL);
	ft_bzero(p, size * nitems);
	return (p);
}