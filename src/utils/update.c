/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/12 18:26:05 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env(void)
{
	free_var((void **)g_minishell.envp);
	g_minishell.envp = creat_valid_envp();
}
/*
Diese Funktion aktualisiert die Anzahl der Argumente in den
Befehlen.
Sie durchläuft die Liste der Befehle in der Minishell-Umgebung und
für jeden Befehl
wird die Anzahl der Argumente (arg_counter) basierend auf den
vorhandenen Argumenten
in der args-Liste aktualisiert. Dies ist hilfreich, um die Anzahl
der Argumente für jeden Befehl aktuell zu halten.
*/

void	update_args_count(int i)
{
	int			command_anzahl;
	t_command	*cmd;

	command_anzahl = g_minishell.command_anzahl;
	while (i < command_anzahl)
	{
		cmd = &g_minishell.commands[i];
		cmd->arg_counter = count_args(cmd->args);
		i++;
	}
}
