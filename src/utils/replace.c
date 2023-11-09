/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/11/09 14:20:24 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_pos(char c, char *set)
{
	int	i;

	i = 0;
	while (c != set[i])
		i++;
	return (i);
}
/*
Die Funktion ersatz_char ersetzt in einem Zeichenarray str alle
Zeichen, die in set1 vorkommen, durch die entsprechenden Zeichen aus set2. 
*/
void	ersatz_char(char *str, char *set1, char *set2, int i)
{
	char	zitat;
	int		ziel_pos;

	zitat = '\0';
	while (str[i])
	{
		if (check_zitat(str[i]) && zitat == '\0')
			zitat = str[i];
		else if (zitat != '\0' && ft_strchr(set1, str[i]))
		{
			ziel_pos = get_pos(str[i], set1);
			str[i] = set2[ziel_pos];
		}
		else if (str[i] == zitat)
			zitat = '\0';
		i++;
	}
}