/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou  <mmanssou@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/09/13 15:23:59 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	len_until_set(char const *s)
{
	int	count;

	count = 0;
	while (!ft_is_space(*s) && *s)
	{
		s++;
		count++;
	}
	return (count);
}

static int	number_of_words(char const *s)
{
	int		count;

	count = 0;
	while (*s)
	{
		if (!ft_is_space(*s))
			count++;
		while (!ft_is_space(*s) && *s)
			s++;
		while (ft_is_space(*s) && *s)
			s++;
	}
	return (count);
}

char	**ft_split(char const *s)
{
	int		i;
	int		words;
	int		len_current_word;
	char	**splitted_string;

	i = 0;
	if (!s)
		return (NULL);
	words = number_of_words(s);
	splitted_string = ft_calloc(words + 1, sizeof(char *));
	while (*s && words != 0)
	{
		if (!ft_is_space(*s))
		{
			len_current_word = len_until_set(s);
			*(splitted_string + i) = ft_substr(s, 0, len_current_word);
			i++;
		}
		while (!ft_is_space(*s) && *s)
			s++;
		while (ft_is_space(*s) && *s)
			s++;
	}
	return (splitted_string);
}
