/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/25 14:13:20 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"

static int	check_leer_zitat(char *str)
{
	if (*str == str[1])
		return (1);
	return (0);
}

static void	remove_outer_zitat(char *str)
{
	int	last_pos;
	int	str_len;

	str_len = ft_strlen(str);
	ft_memmove(str, str + 1, str_len);
	last_pos = str_len - 2;
	ft_memset(str + last_pos, 0, 1);
}

void	hanlde_zitat(char **subtokens)
{
	int	i;

	i = 0;
	while (subtokens[i])
	{
		if (check_zitat(*subtokens[i]) && check_leer_zitat(subtokens[i]))
			ft_memset(subtokens[i], 0, 2);
		else if (check_zitat(*subtokens[i]))
			remove_outer_zitat(subtokens[i]);
		i++;
	}
}