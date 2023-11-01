/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 19:43:44 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

static void	fill_args(char **tokens, int idx)
{
	int	i;
	int	args;

	i = 0;
	args = g_minishell.commands[idx].arg_counter;
	while (i < args)
	{
		g_minishell.commands[idx].args[i] = ft_strdup(tokens[i]);
		i++;
	}
}

static int	cmd_count(char **tokens, int x, int y)
{
	while (tokens[x])
	{
		if (ft_strcmp("|", tokens[x]) == 0)
			y++;
		x++;
	}
	return (y + 1);
}
/*
Diese Funktion initialisiert die Befehle in einer Shell-Struktur. Sie zählt die Anzahl der Befehle,
initialisiert die entsprechenden Datenstrukturen und ruft fill_args auf, um die Argumente für jeden Befehl vorzubereiten.
*/
void	split_save_cmd_struct(char **tokens, int idx)
{
	int		i;
	int		args;
	int		command_anzahl;

	i = 0;
	if (idx == 0)
	{
		g_minishell.command_anzahl = cmd_count(tokens, 0 ,0);
		command_anzahl = g_minishell.command_anzahl;
		g_minishell.commands = ft_calloc(sizeof(t_command), command_anzahl + 1);
	}
	if (tokens[i] == NULL)
		return ;
	while (tokens[i] && ft_strcmp("|", tokens[i]) != 0)
		i++;
	if (tokens[i] && ft_strcmp("|", tokens[i]) == 0)
		i++;
	split_save_cmd_struct(tokens + i, idx + 1);
	args = count_args(tokens);
	g_minishell.commands[idx].arg_counter = args;
	g_minishell.commands[idx].args = ft_calloc(sizeof(char *), args + 1);
	fill_args(tokens, idx);
}

