/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 20:39:44 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"


/*

Die Funktion `fill_status_code` wird in Ihrem Code verwendet, um den Statuscode für einen Befehl zu setzen. Dieser Statuscode gibt an, ob die Ausführung des Befehls erfolgreich war oder nicht. Hier ist eine schrittweise Erklärung der Funktion:

1. Die Funktion `fill_status_code` erhält ein Argument `cmd`, das eine Instanz der Datenstruktur `t_command` darstellt. Diese Struktur enthält Informationen über den auszuführenden Befehl.

2. In der Funktion wird zuerst überprüft, ob der globale Statuscode `g_minishell.status_code` bereits auf 0 gesetzt ist. Wenn dies der Fall ist, wird die Funktion beendet, ohne den Statuscode zu ändern. Dies könnte bedeuten, dass in vorherigen Schritten der Statuscode bereits festgelegt wurde und nicht erneut geändert werden sollte.

3. Die Funktion überprüft dann verschiedene Bedingungen, um den Statuscode zu setzen:

   - Zuerst wird überprüft, ob der Befehl auf ein Verzeichnis verweist (`check_directory(cmd.args[0])`) und ob das Verzeichnis ausführbar ist (`access(cmd.args[0], F_OK | X_OK) == 0`). In diesem Fall wird der Statuscode auf 126 gesetzt. Dies entspricht dem Status "Ist ein Verzeichnis" in der Bash.

   - Dann wird überprüft, ob der Befehl den Pfad zu einer Datei enthält und ob diese Datei nicht existiert (`access(cmd.args[0], F_OK) == -1`). Hier wird der Statuscode auf 127 gesetzt. Dies entspricht dem Status "Datei oder Verzeichnis nicht gefunden" in der Bash.

   - Weiterhin wird geprüft, ob der Befehl ausführbar ist (`access(cmd.args[0], X_OK) == -1`) und ob es sich um eine Datei mit einem Pfad handelt (`ft_strchr(cmd.args[0], 47)`). In diesem Fall wird der Statuscode auf 126 gesetzt.

   - Schließlich wird geprüft, ob der Befehl keinen gültigen Pfad enthält und ob der Statuscode nicht bereits auf 127 oder 126 gesetzt wurde. In diesem Fall wird der Statuscode auf 127 gesetzt.

4. Die Funktion hilft also dabei, den Statuscode für einen Befehl basierend auf verschiedenen Bedingungen festzulegen, die auf die Ausführbarkeit und Existenz des Befehls und die Art des Pfads hinweisen. Dieser Statuscode kann später verwendet werden, um den Erfolg oder das Scheitern der Befehlsausführung im Programm zu verfolgen und anzuzeigen.

Die `fill_status_code`-Funktion trägt zur Behandlung von Fehlern und zur Festlegung des richtigen Statuscodes bei, um das Verhalten des Programms bei der Ausführung von Befehlen besser zu steuern.
*/
void	get_status_code(t_command cmd)
{
	if (g_minishell.status_code == 0)
		return ;
	if (check_directory(cmd.args[0]) && access(cmd.args[0], F_OK | X_OK) == 0 \
			&& ft_strchr(cmd.args[0], 47))
		g_minishell.status_code = 126;
	else if (ft_strchr(cmd.args[0], 47) && cmd.executable_path == NULL \
			&& access(cmd.args[0], F_OK) == -1)
		g_minishell.status_code = 127;
	else if (cmd.executable_path == NULL && cmd.args[0] \
			&& access(cmd.args[0], X_OK) == -1 && ft_strchr(cmd.args[0], 47))
		g_minishell.status_code = 126;
	else if (cmd.executable_path == NULL && cmd.args[0])
		g_minishell.status_code = 127;
}

void	print_error(t_command cmd)
{
	if (check_directory(cmd.args[0]) && access(cmd.args[0], F_OK | X_OK) == 0 \
			&& ft_strchr(cmd.args[0], 47))
		p_fd(STDERR_FILENO, "bash: %s: Is a directory\n", cmd.args[0]);
	else if (ft_strchr(cmd.args[0], 47) && cmd.executable_path == NULL \
			&& access(cmd.args[0], F_OK) == -1)
		p_fd(2, "bash: %s: No such file or directory\n", cmd.args[0]);
	else if (cmd.executable_path == NULL && cmd.args[0] \
			&& access(cmd.args[0], X_OK) == -1 && ft_strchr(cmd.args[0], 47))
		p_fd(STDERR_FILENO, "bash: %s: Permission denied\n", cmd.args[0]);
	else if (cmd.executable_path == NULL && cmd.args[0])
		p_fd(STDERR_FILENO, "%s: command not found\n", cmd.args[0]);
	get_status_code(cmd);
}
