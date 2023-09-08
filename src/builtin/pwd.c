#include "../../inc/minishell.h"
/*
Die Funktion ft_pwd nimmt einen Befehlsparameter cmd entgegen und gibt einen Integer-Wert zurück.

int out: Eine Variable, die den Ausgabekanal speichert.

verwalte_Befehlsausgabe(cmd, &out): Behandelt die Ausgabe des Befehls basierend auf dem Umleitungsstatus (verwalte_Befehlsausgabe).

char *cwd = getcwd(NULL, 0): Ruft das aktuelle Arbeitsverzeichnis mit getcwd ab und speichert es in der Zeichenkette cwd.

if (cmd.args[0]): Überprüft, ob das erste Argument des Befehls vorhanden ist.

ft_printf(out, "%s\n", cwd): Gibt das aktuelle Arbeitsverzeichnis auf dem angegebenen Ausgabekanal (out) aus, gefolgt von einem Zeilenumbruch.

ft_free(cwd): Befreit den Speicher, der für cwd allokiert wurde.

if (g_minishell.on_fork): Überprüft, ob die Shell im Kindprozessmodus ist.

ChildProEnd(0, 0): Beendet den Kindprozess, wenn die Shell im Kindprozessmodus ist.

return 0: Gibt den Rückgabewert 0 zurück, um anzuzeigen, dass der Befehl erfolgreich ausgeführt wurde.
*/
int	ft_pwd(t_command cmd)
{
	char	*cwd;
	int		out;

	out = 1;
	verwalte_Befehlsausgabe(cmd, &out);
	cwd = getcwd(NULL, 0);
	if (cmd.args[0])
	ft_printf2(out, "%s\n", cwd);
	// {
	// 	ft_putstr_fd(cwd, out);
	// 	ft_putstr_fd("\n", out);
	// }
	ft_free(cwd);
	if (g_minishell.on_fork)
		ChildProEnd(0, 0);
	return (0);
}