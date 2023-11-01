/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 19:43:58 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	close_fds(void)
{
	int	i;
	int	commands_size;

	i = 0;
	commands_size = g_minishell.command_anzahl;
	if (g_minishell.commands == NULL)
		return ;
	while (i < commands_size)
	{
		if (g_minishell.commands[i].eingabe != 0)
			close(g_minishell.commands[i].eingabe);
		if (g_minishell.commands[i].ausgabe != 1)
			close(g_minishell.commands[i].ausgabe);
		i++;
	}
}

void	end_alles(void)
{
	int	i;
	int	args;

	i = 0;
	args = g_minishell.command_anzahl;
	close_fds();
	while (i < args)
	{
		ft_free_matrix((void **)g_minishell.commands[i].args);
		ft_free((void *)g_minishell.commands[i].executable_path);
		i++;
	}
	free(g_minishell.commands);
	g_minishell.commands = NULL;
}
