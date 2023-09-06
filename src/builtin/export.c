#include "../../inc/minishell.h"


/*
Druckt die exportierten Umgebungsvariablen auf den Ausgabekanal.
Behandelt die Ausgabe des Befehls basierend auf dem Umleitungsstatus (verwalte_Befehlsausgabe).
Durchläuft die Liste der Umgebungsvariablenknoten und gibt die exportierten Variablen aus.
Verwendet ft_printf, um die Ausgabe im Format "declare
	-x KEY="VALUE"" zu formatieren.
*/
static void	print_export(t_command cmd)
{
	int out;

    out = 1;
	verwalte_Befehlsausgabe(cmd, &out);
	t_node *tmp = g_minishell.envp_list;
	while (tmp)
	{
		if (tmp->key && tmp->value)
		{
			ft_putstr_fd("declare -x ", out);
			ft_putstr_fd(tmp->key, out);
			ft_putstr_fd("\"", out);
			ft_putstr_fd(tmp->value, out);
			ft_putstr_fd("\" \n", out);
		}
		//ft_printf(out, "declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
		{
			ft_putstr_fd("declare -x ", out);
			ft_putstr_fd(tmp->key, out);
			ft_putstr_fd("\n", out);
		}
		//ft_printf(out, "declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}
/*
Führt den Export einer Umgebungsvariable aus.
Überprüft,
	ob die Zeichenkette new_var ein Gleichheitszeichen '=' enthält und ob die Variable bereits in der Umgebungsvariablenliste vorhanden ist.
Wenn new_var kein Gleichheitszeichen enthält und die Variable nicht in der Liste vorhanden ist,
	wird ein neuer Umgebungsvariablenknoten erstellt und der Liste hinzugefügt.
Andernfalls wird new_var in Schlüssel und Wert aufgeteilt und überprüft,
	ob der Schlüssel bereits in der Liste vorhanden ist.
Wenn der Schlüssel nicht vorhanden ist,
	wird ein neuer Umgebungsvariablenknoten erstellt und der Liste hinzugefügt.
Andernfalls wird der Wert der bestehenden Umgebungsvariable geändert.
Der Speicher für die Schlüssel-Wert-Matrix wird freigegeben und die Umgebungsvariablen werden aktualisiert.
*/
static void	exec_export(char *new_var)
{
	char **key_and_value;
	char *key;
	char *value;
	t_node *new_node;

	if (!ft_strchr(new_var, '=') && key_istda(g_minishell.envp_list, new_var))
		return ;
	if (!ft_strchr(new_var, '=') && !key_istda(g_minishell.envp_list, new_var))
	{
		new_node = ft_lstnew(new_var, NULL, NULL);
		ft_lstadd_back(&g_minishell.envp_list, new_node);
		return ;
	}
	key_and_value = erstelle_Schlüssel_Wert_Matrix(new_var);
	key = key_and_value[0];
	value = key_and_value[1];
	if (!key_istda(g_minishell.envp_list, key))
	{
		new_node = ft_lstnew(key, value, new_var);
		ft_lstadd_back(&g_minishell.envp_list, new_node);
	}
	else
		andere_envp(&g_minishell.envp_list, key, value);
	FreeMatrix((void **)key_and_value);
	update_env();
}

static int	is_valid_identifier2(const char *var)
{
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);

	for (int i = 1; var[i] && var[i] != '='; i++)
	{
		if (!is_bash_char(var[i]))
			return (0);
	}

	return (1);
}
/*
Implementiert den Befehl "export" in einer Shell.
Überprüft,
	ob der Befehl keine Argumente hat. In diesem Fall werden die exportierten Variablen gedruckt und der Status bleibt unverändert.
Durchläuft die Argumente des Befehls ab dem zweiten Argument.
Überprüft, ob jedes Argument ein gültiger Bezeichner ist.
Wenn es sich nicht um einen gültigen Bezeichner handelt,
	wird eine Fehlermeldung ausgegeben und der Status wird auf 1 gesetzt.
Andernfalls wird der Export der Umgebungsvariable mit exec_export durchgeführt.
Wenn die Shell im Kindprozessmodus ist, wird ChildProEnd aufgerufen,
	um den Kindprozess zu beenden.
Der Status wird zurückgegeben.
*/
void	print_error_export(int fd, char *str)
{
	ft_putstr_fd("bash: export: '", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("': not a valid identifier\n", fd);
}

int	ft_export(t_command cmd)
{
	int i = 1;
	int status = 0;

	if (cmd.number_of_args == 1)
	{
		print_export(cmd);
		return (status);
	}
	while (cmd.args[i])
	{
		if (!is_valid_identifier2(cmd.args[i]))
		{
			print_error_export(STDERR_FILENO, cmd.args[i]);
			//ft_printf(STDERR_FILENO,
			//		"bash: export: `%s': not a valid identifier\n",
			//		cmd.args[i]);
			status = 1;
		}
		else
			exec_export(cmd.args[i]);
		i++;
	}
	if (g_minishell.on_fork)
		ChildProEnd(0, status);
	return (status);
}
