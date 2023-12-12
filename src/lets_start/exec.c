/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/12 18:11:44 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//split_save_cmd_struct: alle commands lesen und zählen und dann
//in die struct t_command speichern
//handle_files: get in der command und sucht nach file name und
//setzt es zu null
static void	setup_execution_context(char **command_tokens)
{
	split_save_cmd_struct(command_tokens, 0);
	free_var((void **)command_tokens);
	handle_files(0);
	if (get_redirect(0) != 3)
		ft_destroy();
}
/*
Diese Funktion führt einen einzelnen Shell-Befehl aus. Sie prüft,
ob der Befehl ein eingebauter Befehl ist und führt diesen gegebenenfalls aus.
Falls nicht, erstellt sie einen Kindprozess, in dem der Befehl ausgeführt wird.
*/

static int	execute_command(t_command cmd)
{
	int	process_id;

	if (get_befehl(cmd.args[0]) != -1)
		return (execute_builtin_command(cmd,
				g_minishell.builtins[get_befehl(cmd.args[0])]), -1);
	process_id = fork();
	g_minishell.in_child_process = 1;
	if (process_id == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (cmd.eingabe == -1 || cmd.ausgabe == -1)
			end_pro_child(0, 1);
		if (cmd.error && get_befehl(cmd.args[0]) == -1)
			end_pro_child(0, cmd.error);
		if (cmd.executable_path && cmd.args[0])
		{
			dup2(cmd.eingabe, 0);
			dup2(cmd.ausgabe, 1);
			child_fd_close();
			execve(cmd.executable_path, cmd.args, g_minishell.envp);
		}
		end_pro_child(0, cmd.error);
	}
	return (process_id);
}

static void	wait_for_child_processes(int pid, int *status, int i)
{
	int	command_anzahl;

	command_anzahl = g_minishell.command_anzahl;
	waitpid(pid, status, 0);
	while (++i < command_anzahl - 1)
		wait(NULL);
	if (WIFEXITED(*status))
		g_minishell.status_code = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		g_minishell.status_code = 128 + WTERMSIG(*status);
}

static void	check_error(int i)
{
	int			size;
	t_command	cmd;

	size = g_minishell.command_anzahl;
	while (i < size && get_befehl(g_minishell.commands[i].args[0]) == -1)
	{
		cmd = g_minishell.commands[i];
		print_error(cmd);
		i++;
	}
}

void	run_command(char **command_tokens, int index, int exit_status)
{
	int	process_id;

	setup_execution_context(command_tokens);
	update_args_count(0);
	get_pfad(0);
	if (g_minishell.heredoc.heredoc_exited == 1)
	{
		g_minishell.status_code = 130;
		g_minishell.heredoc.heredoc_exited = 0;
		return ;
	}
	if (g_minishell.command_anzahl > 1)
	{
		while (++index < g_minishell.command_anzahl)
			process_id = handel_get_bid_exe(index,
					&g_minishell.commands[index]);
	}
	else
		process_id = execute_command(g_minishell.commands[0]);
	if (process_id != -1)
		wait_for_child_processes(process_id, &exit_status, -1);
	g_minishell.in_child_process = 0;
	check_error(0);
	cleanup_all_resources(0);
}
