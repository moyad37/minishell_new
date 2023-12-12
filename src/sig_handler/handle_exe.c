/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/12 18:01:24 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Diese Funktion behandelt die Duplizierung (Umleitung) der Eingabe-
und Ausgabestreams
für den aktuellen Befehl. Sie verwendet dup2,
	um die Standard-Streams (STDIN und STDOUT)
entsprechend zu setzen,
	abhängig von den Umleitungen und der Reihenfolge der Befehle.
*/
static void	handel_in_out_put(t_command *previous_command, t_command *curr,
		t_command *next)
{
	if (!previous_command)
		dup2(curr->eingabe, STDIN_FILENO);
	else
	{
		if (curr->eingabe == STDIN_FILENO)
			dup2(previous_command->pipe[0], STDIN_FILENO);
		else
			dup2(curr->eingabe, STDIN_FILENO);
	}
	if (!next)
		dup2(curr->ausgabe, STDOUT_FILENO);
	else
	{
		if (curr->ausgabe == STDOUT_FILENO)
			dup2(curr->pipe[1], STDOUT_FILENO);
		else
			dup2(curr->ausgabe, STDOUT_FILENO);
	}
}
/*
Diese Funktion startet die Ausführung eines Befehls oder einer Befehlskette.
Sie erstellt ggf. eine pipe zwischen den Befehlen,
	um die Kommunikation zwischen ihnen zu
ermöglichen. Dann wird ein Kindprozess (fork) erstellt,
	in dem der Befehl ausgeführt wird.
Die Funktion überprüft auch,
	ob derz Befehl ein eingebauter Befehl ist und führt diesen in
	einem separaten Verarbeitungszweig aus.
*/

static int	mach_command(t_command *previous_command, t_command *curr,
		t_command *next)
{
	int	process_id;
	int	builtin_pos;

	if (next)
		pipe(curr->pipe);
	process_id = fork();
	g_minishell.in_child_process = 1;
	if (process_id == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (curr->eingabe == -1 || curr->ausgabe == -1)
			end_pro_child(0, 1);
		builtin_pos = get_befehl(curr->args[0]);
		if (builtin_pos != -1)
			execute_builtin_command(*curr, g_minishell.builtins[builtin_pos]);
		if (curr->executable_path && curr->args[0])
		{
			handel_in_out_put(previous_command, curr, next);
			child_fd_close();
			execve(curr->executable_path, curr->args, g_minishell.envp);
		}
		end_pro_child(0, curr->error);
	}
	return (process_id);
}
/*
Diese Funktion koordiniert die Ausführung eines Befehls in einer
Befehlskette. Sie überwacht,
ob der Befehl der erste oder letzte in der Kette ist,
	und sorgt für die richtige Kommunikation
zwischen den Befehlen,
	indem sie die Duplizierung der Eingabe- und Ausgabestreams behandelt.
*/

int	handel_get_bid_exe(int idx, t_command *curr)
{
	int			process_id;
	t_command	previous_command;
	t_command	next_command;

	if (idx == 0)
	{
		next_command = g_minishell.commands[idx + 1];
		process_id = mach_command(NULL, curr, &next_command);
		close(g_minishell.commands[idx].pipe[1]);
	}
	else if (idx == g_minishell.command_anzahl - 1)
	{
		previous_command = g_minishell.commands[idx - 1];
		process_id = mach_command(&previous_command, curr, NULL);
		close(g_minishell.commands[idx - 1].pipe[0]);
	}
	else
	{
		next_command = g_minishell.commands[idx + 1];
		previous_command = g_minishell.commands[idx - 1];
		process_id = mach_command(&previous_command, curr, &next_command);
		close(previous_command.pipe[0]);
		close(curr->pipe[1]);
	}
	return (process_id);
}
