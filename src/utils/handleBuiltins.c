/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleBuiltins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 19:46:03 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_befehl(char *str)
{
	if (!str)
		return (-1);
	if (ft_strcmp(str, "echo") == 0)
		return (0);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (2);
	else if (ft_strcmp(str, "export") == 0)
		return (3);
	else if (ft_strcmp(str, "unset") == 0)
		return (4);
	else if (ft_strcmp(str, "env") == 0)
		return (5);
	else if (ft_strcmp(str, "exit") == 0)
		return (6);
	return (-1);
}

// void	check_input_with_pipe(t_command cmd, int *fd)
// {
// 	if (cmd.eingabe != STDIN_FILENO)
// 		*fd = cmd.eingabe;
// 	else if (cmd.pipe[0] != 0)
// 		*fd = cmd.pipe[0];
// }

void	check_output_with_pipe(t_command cmd, int *fd)
{
	if (cmd.ausgabe != STDOUT_FILENO)
		*fd = cmd.ausgabe;
	else if (cmd.pipe[1] != 0)
		*fd = cmd.pipe[1];
}

void	execute_builtin_command(t_command cmd, int (*builtin)(t_command cmd))
{
	if (g_minishell.in_child_process)
		builtin(cmd);
	else
	{
		if (ft_strcmp(cmd.args[0], "exit") == 0)
			g_minishell.status_code = builtin(cmd);
		g_minishell.status_code = builtin(cmd);
	}
}
