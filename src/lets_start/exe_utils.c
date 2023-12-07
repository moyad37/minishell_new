/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/06 21:58:05 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
1.Nimmt einen Index (i) als Parameter.
2.Ruft den Umgebungsvariablenwert für "PATH" ab.
3.Trennt den PATH-String in Verzeichnisse auf, die durch ':' getrennt sind, und fügt am Ende jedes Verzeichnisses einen Schrägstrich ('/') hinzu.
4.Gibt ein Array von Zeichenketten zurück, das die Verzeichnisse im PATH repräsentiert.
*/
static char	**hol_pfad_verzeichnisse(int i)
{
	char	*path;
	char	**pfad_directories;

	path = get_key_value(g_minishell.envp_list, "PATH");
	pfad_directories = seperat_by_c(path, ':');
	while (pfad_directories[i])
	{
		append(&pfad_directories[i], ft_strdup("/"));
		i++;
	}
	return (pfad_directories);
}
/*
1.Nimmt einen Befehlszeiger (command) und einen Startindex (i) als Parameter.
2.Ruft die Verzeichnisse im PATH ab und iteriert durch jedes Verzeichnis, um den vollständigen Pfad zum auszuführenden Befehl zu erstellen.
3.Überprüft, ob die Datei im Verzeichnis existiert und ausführbar ist.
4.Gibt den vollständigen Pfad zurück, wenn erfolgreich, andernfalls NULL.
*/
static char	*find_pfad(t_command *command, int i)
{
	char	*executable_path;
	char	**pfad_directories;

	pfad_directories = hol_pfad_verzeichnisse(0);
	while (pfad_directories[i] && command->args[0] && ft_strlen(command->args[0]) > 0)
	{
		executable_path = ft_strjoin(pfad_directories[i], command->args[0]);
		if (!check_directory(executable_path) && access(executable_path, F_OK | X_OK) == 0)
		{
			free_var((void **)pfad_directories);
			return (executable_path);
		}
		else if (access(executable_path, F_OK) == 0 && access(executable_path, X_OK) == -1)
		{
			command->error = 13;
			ft_free(executable_path);
			break ;
		}
		ft_free(executable_path);
		i++;
	}
	free_var((void **)pfad_directories);
	return (NULL);
}
/*
1.Nimmt einen Befehlszeiger (cmd) als Parameter.
2.Setzt den Fehlercode im Befehlsobjekt auf 0.
3.Überprüft, ob der Befehl im aktuellen Verzeichnis ausführbar ist.
4.Wenn nicht, ruft find_pfad auf, um den vollständigen Pfad zu suchen.
5.Setzt den Fehlercode im Befehlsobjekt basierend auf verschiedenen Bedingungen
wie fehlender Befehlsname, Verzeichnis oder fehlender Ausführungsrechte.
6.Setzt cmd->executable_path auf den gefundenen vollständigen Pfad oder NULL, wenn der Befehl nicht gefunden wurde.
*/
static void	bin_pfad(t_command *cmd)
{
	cmd->error = 0;
	if (cmd->args[0] && access(cmd->args[0], F_OK | X_OK) == 0 \
			&& !check_directory(cmd->args[0]))
		cmd->executable_path = ft_strdup(cmd->args[0]);
	else
		cmd->executable_path = find_pfad(cmd, 0);
	if (cmd->executable_path && cmd->args[0] == NULL)
		cmd->error = 1;
	else if (check_directory(cmd->args[0]) && access(cmd->args[0], F_OK | X_OK) == 0)
		cmd->error = 126;
	else if (ft_strchr(cmd->args[0], 47) && cmd->executable_path == NULL)
		cmd->error = 2;
	else if (cmd->error == 0 && cmd->executable_path == NULL)
		cmd->error = 127;
}
/*
Diese Funktion initialisiert den Binärpfad für die Befehle in der Minishell-Umgebung.
Sie ruft bin_pfad für jeden Befehl auf, um den Binärpfad festzulegen.

Initialisiert den Binärpfad für die Befehle in der Minishell-Umgebung, indem sie bin_pfad für jeden Befehl aufruft.
*/
void	get_pfad(int i)
{
	int	command_anzahl;

	command_anzahl = g_minishell.command_anzahl;
	while (i < command_anzahl)
	{
		bin_pfad(&g_minishell.commands[i]);
		i++;
	}
}
