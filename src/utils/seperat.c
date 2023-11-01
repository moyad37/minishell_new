/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:56:05 by mmanssou          #+#    #+#             */
/*   Updated: 2023/09/15 13:56:37 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	WordsCount(const char *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
			words++;
		while (*s && *s != c)
			s++;
	}
	return (words);
}

char	**seperatByC(const char *str, char c)
{
	int		i;
	char	**lst;
	size_t	curr_word_len;

	i = 0;
	if (!str)
		return (0);
	lst = (char **)ft_calloc(sizeof(char *), WordsCount(str, c) + 1);
	if (!lst)
		return (0);
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
		{
			if (!ft_strchr(str, c))
				curr_word_len = ft_strlen((char *)str);
			else
				curr_word_len = ft_strchr(str, c) - str;
			lst[i++] = ft_substr(str, 0, curr_word_len);
			str += curr_word_len;
		}
	}
	return (lst);
}
