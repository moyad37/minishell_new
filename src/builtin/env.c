#include "../../inc/minishell.h"
/*
Die Funktion ft_env nimmt einen Befehlsparameter cmd entgegen und gibt einen Integer-Wert zurück.

int out: Eine Variable, die den Ausgabekanal speichert.

handle_output(cmd, &out): Behandelt die Ausgabe des Befehls basierend auf dem Umleitungsstatus (handle_output).

if (cmd.args[0]): Überprüft, ob das erste Argument des Befehls vorhanden ist.

ft_print_matrix_fd(g_minishell.envp, out): Gibt die Umgebungsvariablenmatrix (g_minishell.envp) auf den angegebenen Ausgabekanal (out) aus.

if (g_minishell.on_fork): Überprüft, ob die Shell im Kindprozessmodus ist.

die_child(0, 0): Beendet den Kindprozess, wenn die Shell im Kindprozessmodus ist.

return (0): Gibt den Rückgabewert 0 zurück, um anzuzeigen, dass der Befehl erfolgreich ausgeführt wurde.
*/
int	ft_env(t_command cmd)
{
	int	out;

	out = 1;
	handle_output(cmd, &out);
	if (cmd.args[0])
		ft_print_matrix_fd(g_minishell.envp, out);
	if (g_minishell.on_fork)
		die_child(0, 0);
	return (0);
}