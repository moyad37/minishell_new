/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/11/13 20:47:23 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			command->error = EACCES;
			ft_free(executable_path);
			break ;
		}
		ft_free(executable_path);
		i++;
	}
	free_var((void **)pfad_directories);
	return (NULL);
}

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
		cmd->error = EISDIR;
	else if (ft_strchr(cmd->args[0], 47) && cmd->executable_path == NULL)
		cmd->error = ENOENT;
	else if (cmd->error == 0 && cmd->executable_path == NULL)
		cmd->error = ENOCMD;
}
/*
Diese Funktion initialisiert den Binärpfad für die Befehle in der Minishell-Umgebung.
Sie ruft bin_pfad für jeden Befehl auf, um den Binärpfad festzulegen.
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
