/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/12 18:16:01 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	spizial_char_count(char *cmd)
{
	int	count;
	int	metachars_count;

	count = 0;
	metachars_count = 0;
	while (cmd[count])
	{
		if (check_pipe(cmd[count]))
			metachars_count++;
		count++;
	}
	return (metachars_count);
}
/*
macht malloc für den command und speichert es in eine neue variable
*/

char	*init_for_cmd(char *input)
{
	char	*formatted_input;
	int		lehrzeichen_count_max;

	lehrzeichen_count_max = spizial_char_count(input) * 2;
	formatted_input = malloc(sizeof(char) * (lehrzeichen_count_max
				+ ft_strlen(input) + 2));
	if (!formatted_input)
		return (NULL);
	ft_bzero(formatted_input, (lehrzeichen_count_max + ft_strlen(input) + 2));
	ft_strlcpy(formatted_input, input, (lehrzeichen_count_max + ft_strlen(input)
			+ 2));
	return (formatted_input);
}
