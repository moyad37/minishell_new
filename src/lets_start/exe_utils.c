/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 19:43:46 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**hol_pfad_verzeichnisse(void)
{
	int		i;
	char	*path;
	char	**path_dirs;

	i = 0;
	path = get_key_value(g_minishell.envp_list, "PATH");
	path_dirs = seperatByC(path, ':');
	while (path_dirs[i])
	{
		append(&path_dirs[i], ft_strdup("/"));
		i++;
	}
	return (path_dirs);
}

static char	*find_pfad(t_command *command)
{
	int		i;
	char	*bin;
	char	**path_dirs;

	i = 0;
	path_dirs = hol_pfad_verzeichnisse();
	while (path_dirs[i] && command->args[0] && ft_strlen(command->args[0]) > 0)
	{
		bin = ft_strjoin(path_dirs[i], command->args[0]);
		if (!check_directory(bin) && access(bin, F_OK | X_OK) == 0)
		{
			ft_free_matrix((void **)path_dirs);
			return (bin);
		}
		else if (access(bin, F_OK) == 0 && access(bin, X_OK) == -1)
		{
			command->error = EACCES;
			ft_free(bin);
			break ;
		}
		ft_free(bin);
		i++;
	}
	ft_free_matrix((void **)path_dirs);
	return (NULL);
}

static void	bin_pfad(t_command *cmd)
{
	cmd->error = 0;
	if (cmd->args[0] && access(cmd->args[0], F_OK | X_OK) == 0 \
			&& !check_directory(cmd->args[0]))
		cmd->executable_path = ft_strdup(cmd->args[0]);
	else
		cmd->executable_path = find_pfad(cmd);
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
	int	args;

	args = g_minishell.command_anzahl;
	while (i < args)
	{
		bin_pfad(&g_minishell.commands[i]);
		i++;
	}
}
