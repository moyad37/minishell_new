/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/11/10 14:12:02 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setup_execution_context(char **tokens)
{
	//alle commands lesen und zählen und dann in die struct t_command speichern
	split_save_cmd_struct(tokens, 0);
	ft_free_matrix((void **)tokens);
	//get in der command und sucht nach file name und setzt es zu null
	handle_files(0);
	
	//ab hier kann ich zu andere funktion rein hüpfen und die letzten zwei kann ich in funktion executor schreiben
	if(get_redirect(0) != 3)
		ft_destroy();
	//init_redirects();
	// remove_redirects();
	// losche_zitat();
	// update_args_count(0);
	// get_pfad(0);
}
/*
Diese Funktion führt einen einzelnen Shell-Befehl aus. Sie prüft,
ob der Befehl ein eingebauter Befehl ist und führt diesen gegebenenfalls aus.
Falls nicht, erstellt sie einen Kindprozess, in dem der Befehl ausgeführt wird.
*/
static int	execute_command(t_command cmd)
{
	int	pid;

	if (get_befehl(cmd.args[0]) != -1)
	{
		//execute_builtin_command(cmd, g_minishell.builtins[get_befehl(cmd.args[0])]);
		return (execute_builtin_command(cmd, g_minishell.builtins[get_befehl(cmd.args[0])]), -1);
	}
	pid = fork();
	g_minishell.in_child_process = 1;
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (cmd.eingabe == -1 || cmd.ausgabe == -1)
			end_pro_child(0, 1);
		if (cmd.error && get_befehl(cmd.args[0]) == -1)
			end_pro_child(0, cmd.error);
		if (cmd.executable_path && cmd.args[0])
		{
			//make_dups(cmd);
			dup2(cmd.eingabe, 0);
			dup2(cmd.ausgabe, 1);
			child_fd_close();
			execve(cmd.executable_path, cmd.args, g_minishell.envp);
		}
		end_pro_child(0, cmd.error);
	}
	return (pid);
}

static void	wait_for_child_processes(int pid, int *status)
{
	int	i;
	int	size;

	i = -1;
	size = g_minishell.command_anzahl;
	waitpid(pid, status, 0);
	while (++i < size - 1)
		wait(NULL);
	if (WIFEXITED(*status))
		g_minishell.status_code = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		g_minishell.status_code = 128 + WTERMSIG(*status);
}

static void	check_error(void)
{
	int			i;
	int			size;
	t_command	cmd;

	i = 0;
	size = g_minishell.command_anzahl;
	while (i < size && get_befehl(g_minishell.commands[i].args[0]) == -1)
	{
		cmd = g_minishell.commands[i];
		print_error(cmd);
		i++;
	}
}

void	executor(char **tokens, int i, int status)
{
	int	pid;

	setup_execution_context(tokens);
	update_args_count(0);
	get_pfad(0);
	if (g_minishell.heredoc.heredoc_exited == 1)
	{
		g_minishell.status_code = 130;
		g_minishell.heredoc.heredoc_exited = 0;
		return ;
	}
	if (g_minishell.command_anzahl > 1)
		while (++i < g_minishell.command_anzahl)
			pid = handel_get_bid_exe(i, &g_minishell.commands[i]);
	else
		pid = execute_command(g_minishell.commands[0]);
	if (pid != -1)
		wait_for_child_processes(pid, &status);
	g_minishell.in_child_process = 0;
	check_error();
	end_alles();
}
