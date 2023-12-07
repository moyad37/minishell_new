/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/06 22:04:31 by mmanssou         ###   ########.fr       */
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
/*
1.Nimmt einen Befehlszeiger (cmd) und einen Dateinamen (filename) als Parameter.
2.Ruft die entsprechende Fehlerfunktion basierend auf dem Befehlszustand auf (Eingabe oder Ausgabe).
*/
static void	configure_streams(t_command *cmd, int i)
{
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
			return (handle_error(cmd, cmd->args[i + 1]));
		}
		if (check_redirect(cmd->args[i]))
			i++;
		i++;
	}
}
/*
Initialisiert die Umleitungen für alle Befehle im globalen g_minishell.commands-Array, beginnend mit dem angegebenen Index.
*/
void	init_redirects(int i)
{
	int	command_anzahl;

	command_anzahl = g_minishell.command_anzahl;
	while (i < command_anzahl && !g_minishell.heredoc.heredoc_exited)
	{
		configure_streams(&g_minishell.commands[i], 0);
		i++;
	}
}
/*
Initialisiert die Umleitungen für alle Befehle und bereinigt anschließend die Umleitungen und Zitate.
*/
int	get_redirect(int i)
{
	init_redirects(0);
	i++;
	losche_umleitung(0);
	i++;
	losche_zitat();
	i++;
	if(i != 3)
		return (0);
	return (i);
}