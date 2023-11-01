/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/24 13:51:23 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

static int	spizial_char_count(char *cmd)
{
	int		i;
	int		amount_of_metachars;

	i = 0;
	amount_of_metachars = 0;
	while (cmd[i])
	{
		if (check_pipe(cmd[i]))
			amount_of_metachars++;
		i++;
	}
	return (amount_of_metachars);
}
/*
macht malloc für den command und speichert es in eine neue variable
*/
char	*init_for_cmd(char *cmd)
{
	char	*new_cmd;
	int		mem_to_alloc;
	int		max_spaces_to_insert;

	max_spaces_to_insert = spizial_char_count(cmd) * 2;
	mem_to_alloc = max_spaces_to_insert + ft_strlen(cmd) + 2;
	new_cmd = malloc(sizeof(char) * mem_to_alloc);
	if(!new_cmd)
		return (NULL);
	ft_bzero(new_cmd, mem_to_alloc);
	ft_strlcpy(new_cmd, cmd, mem_to_alloc);
	//printf("init_for_cmd return = %s\n", new_cmd);
	return (new_cmd);
}