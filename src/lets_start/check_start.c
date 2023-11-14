/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/11/14 12:27:51 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	format_foppelt_pipe_leerzeichen(char *text, int position)
{
	int	count_changes;

	count_changes = 0;
	if (position != 0 && *(text - 1) != ' ')
	{
		ft_memmove(text + 1, text, ft_strlen(text));
		text[0] = ' ';
		count_changes++;
		if (text[3] != ' ')
		{
			ft_memmove(text + 4, text + 3, ft_strlen(text));
			text[3] = ' ';
			count_changes++;
		}
	}
	else if (text[2] != ' ')
	{
		ft_memmove(text + 3, text + 2, ft_strlen(text));
		text[2] = ' ';
		count_changes++;
	}
	return (count_changes);
}

char	**check_commands(char *cmd)
{
	char	**tokens;

	tokens = NULL;
	if (cmd == NULL)
		ft_destroy();
	if (cmd[0] == '\0')
		ft_free(cmd);
	else
	{
		add_history(cmd);
		tokens = lexer(cmd, -1);
		if (*tokens == NULL)
			return (NULL);
		ft_free(cmd);
		if (parser(&tokens, 0) == 1 || *tokens == NULL)
		{
			//printf("parser_error\n");
			free_var((void **)tokens);
			return (NULL);
		}
	}
	return (tokens);
}
