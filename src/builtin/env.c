#include "../../inc/minishell.h"
/*
Die Funktion ft_env nimmt einen Befehlsparameter cmd entgegen und gibt einen Integer-Wert zurück.

int out: Eine Variable, die den Ausgabekanal speichert.

verwalte_Befehlsausgabe(cmd, &out): Behandelt die Ausgabe des Befehls basierend auf dem Umleitungsstatus (verwalte_Befehlsausgabe).

if (cmd.args[0]): Überprüft, ob das erste Argument des Befehls vorhanden ist.

print_matrix_to_fd(g_minishell.envp, out): Gibt die Umgebungsvariablenmatrix (g_minishell.envp) auf den angegebenen Ausgabekanal (out) aus.

if (g_minishell.on_fork): Überprüft, ob die Shell im Kindprozessmodus ist.

ChildProEnd(0, 0): Beendet den Kindprozess, wenn die Shell im Kindprozessmodus ist.

return (0): Gibt den Rückgabewert 0 zurück, um anzuzeigen, dass der Befehl erfolgreich ausgeführt wurde.
*/
int	ft_env(t_command cmd)
{
	int	out;

	out = 1;
	verwalte_Befehlsausgabe(cmd, &out);
	if (cmd.args[0])
		print_matrix_to_fd(g_minishell.envp, out);
	if (g_minishell.on_fork)
		ChildProEnd(0, 0);
	return (0);
}