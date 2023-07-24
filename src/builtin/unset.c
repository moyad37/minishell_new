#include "../../inc/minishell.h"

/*
Überprüft, ob eine gegebene Zeichenkette (var) ein gültiger Bezeichner ist.
Überprüft, ob das erste Zeichen kein Buchstabe (!ft_isalpha(var[0])) und kein Unterstrich (var[0] != '_') ist.
Durchläuft die Zeichenkette ab dem zweiten Zeichen und überprüft, ob jedes Zeichen ein gültiges Bash-Zeichen ist (!is_bash_char(var[i])).
Gibt 1 zurück, wenn die Zeichenkette ein gültiger Bezeichner ist.
*/
static int is_valid_identifier(const char *var)
{
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return 0;

	for (int i = 1; var[i] && var[i] != '='; i++)
	{
		if (!is_bash_char(var[i]))
			return 0;
	}

	return 1;
}
/*
Löscht einen bestimmten Umgebungsvariablenknoten aus der Liste (envp_list) basierend auf dem Schlüssel (key).
Durchläuft die Liste, um den entsprechenden Knoten zu finden.
Wenn der erste Knoten der zu löschende Knoten ist, wird der Anfang der Liste auf den nächsten Knoten gesetzt und der erste Knoten wird freigegeben.
Andernfalls wird der vorherige Knoten mit dem nächsten Knoten verbunden und der zu löschende Knoten wird freigegeben.
*/
void delet_specific_node(t_node **envp_list, const char *key)
{
	t_node *curr = *envp_list;
	t_node *prev = *envp_list;

	if (ft_strcmp(curr->key, key) == 0)
	{
		*envp_list = (*envp_list)->next;
		ft_lstdelone(curr, &free);
		return;
	}

	while (curr && ft_strcmp(curr->key, key) != 0)
	{
		prev = curr;
		curr = curr->next;
	}

	if (!curr)
		return;

	prev->next = curr->next;
	ft_lstdelone(curr, &free);
}
/*
Führt das Unsetzen einer Umgebungsvariable aus.
Überprüft, ob die Zeichenkette delet_var ein gültiger Bezeichner ist.
Wenn es sich nicht um einen gültigen Bezeichner handelt, wird eine Fehlermeldung ausgegeben und der Status wird auf 1 gesetzt.
Überprüft, ob der Schlüssel in der Umgebungsvariablenliste vorhanden ist.
Wenn der Schlüssel vorhanden ist, wird der entsprechende Umgebungsvariablenknoten gelöscht und die Umgebungsvariablen werden 
*/
static int exec_unset(char *delet_var)
{
	if (!is_valid_identifier(delet_var))
	{
		ft_printf(STDERR_FILENO, "bash: unset: `%s': not a valid identifier\n", delet_var);
		return 1;
	}

	if (key_exists(g_minishell.envp_list, delet_var))
	{
		delet_specific_node(&g_minishell.envp_list, delet_var);
		update_env();
	}

	return 0;
}
/*
Implementiert den Befehl "unset" in einer Shell.
Überprüft, ob der Befehl mehr als ein Argument hat.
Durchläuft die Argumente des Befehls ab dem zweiten Argument.
Ruft exec_unset für jedes Argument auf und überprüft den Rückgabewert.
Wenn exec_unset einen Fehler zurückgibt, wird der Status auf 1 gesetzt.
Wenn die Shell im Kindprozessmodus ist, wird die_child aufgerufen, um den Kindprozess zu beenden.
Der Status wird zurückgegeben.
*/
int ft_unset(t_command cmd)
{
	int i = 1;
	int status = 0;

	if (cmd.number_of_args > 1)
	{
		while (cmd.args[i])
		{
			if (exec_unset(cmd.args[i]))
				status = 1;
			i++;
		}
	}

	if (g_minishell.on_fork)
		die_child(0, status);

	return status;
}
