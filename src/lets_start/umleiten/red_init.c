/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 19:43:52 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"


/*
Diese Funktion wird verwendet, um die Ausgabedatei (Standardausgabe) eines Befehls auf eine bestimmte
Datei umzuleiten. Sie überprüft den redirect-Parameter, um zu bestimmen, ob es sich um eine Neuerstellung
(">") oder eine Anhängung (">>") handelt, und öffnet die Datei entsprechend. Dann wird der Ausgabestrom des
Befehls auf diese Datei umgeleitet.
*/
static void	setze_ausgabe(t_command *cmd, char *redirect, char *filename)
{
	int	flags;

	if (ft_strcmp(">", redirect) == 0)
	{
		flags = O_CREAT | O_WRONLY | O_TRUNC;
		swap_stream_fd("output", cmd, open(filename, flags, 0644));
	}
	else
	{
		flags = O_CREAT | O_WRONLY | O_APPEND;
		swap_stream_fd("output", cmd, open(filename, flags, 0644));
	}
}
/*
Diese Funktion wird verwendet, um die Eingabedatei (Standard-Eingabe) eines Befehls auf eine
bestimmte Datei umzuleiten. Sie überprüft den redirect-Parameter, um zu bestimmen, ob es sich
um eine Eingabeumleitung ("<") oder Heredoc (eine Methode zur Eingabe von Daten in eine Datei) handelt.
*/
static void	setze_eingabe(t_command *cmd, char *redirect, char *filename)
{
	char	*delim;

	if (ft_strcmp("<", redirect) == 0)
		swap_stream_fd("input", cmd, open(filename, O_RDONLY));
	else
	{
		delim = filename;
		g_minishell.heredoc.heredoc_exited = heredoc(cmd, delim);
	}
}

static void	configure_streams(t_command *cmd)
{
	int	i;

	i = 0;
	cmd->eingabe = 0;
	cmd->ausgabe = 1;
	while (cmd->args[i])
	{
		if (check_red_input(cmd->args[i]))
			setze_eingabe(cmd, cmd->args[i], cmd->args[i + 1]);
		else if (check_red_output(cmd->args[i]))
			setze_ausgabe(cmd, cmd->args[i], cmd->args[i + 1]);
		if (check_command_errors(cmd))
		{
			handle_error(cmd, cmd->args[i + 1]);
			return ;
		}
		if (is_redirect(cmd->args[i]))
			i++;
		i++;
	}
}

void	init_redirects(void)
{
	int	i;
	int	args;

	i = 0;
	args = g_minishell.command_anzahl;
	while (i < args && !g_minishell.heredoc.heredoc_exited)
	{
		configure_streams(&g_minishell.commands[i]);
		i++;
	}
}

int	get_redirect(int i)
{
	init_redirects();
	i++;
	losche_umleitung();
	i++;
	losche_zitat();
	i++;
	if(i != 3)
		return (0);
	return (i);
}