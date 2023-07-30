#include "../../inc/minishell.h"

/*
Diese Funktion tauscht die aktuellen Arbeitsverzeichnisse (PWD und OLDPWD) aus.
Sie speichert das aktuelle Verzeichnis in oldpwd.
Überprüft, ob die Schlüssel "OLDPWD" und "PWD" in der Umgebungsvariablenliste vorhanden sind.
Ändert den Wert von "OLDPWD" auf das gespeicherte oldpwd.
Ändert das Arbeitsverzeichnis auf das neue Verzeichnis (new_dir).
Speichert das aktualisierte Arbeitsverzeichnis in pwd.
Ändert den Wert von "PWD" auf das gespeicherte pwd.
Befreit den Speicher von oldpwd und pwd.
*/
void	swap_pwds(char *new_dir)
{
	/*
	char	*pwd;
	t_node	**envp;

	envp = &g_minishell.envp_list;
	pwd = getcwd(NULL, 0);
	if (key_exists(*envp, "OLDPWD"))
		change_value_from_key(envp, "OLDPWD", pwd);
	ft_free(pwd);
	chdir(new_dir);
	pwd = getcwd(NULL, 0);
	if (key_exists(*envp, "PWD"))
		change_value_from_key(envp, "PWD", pwd);
	ft_free(pwd);
	*/
	t_node **envp = &g_minishell.envp_list;

    char *oldpwd = NULL;
    char *pwd = NULL;

    if (key_exists(*envp, "OLDPWD")) {
        oldpwd = getcwd(NULL, 0);
        change_value_from_key(envp, "OLDPWD", oldpwd);
    }

    chdir(new_dir);

    if (key_exists(*envp, "PWD")) {
        pwd = getcwd(NULL, 0);
        change_value_from_key(envp, "PWD", pwd);
    }

    ft_free(oldpwd);
    ft_free(pwd);

}
/*
Diese Funktion ändert das Arbeitsverzeichnis basierend auf dem Wert der Umgebungsvariablen "HOME".
Ruft swap_pwds auf und übergibt den Wert von "HOME".
Wenn der Wert von "HOME" leer ist, gibt die Funktion einen Fehler aus und gibt 1 zurück.
*/
int	change_home(void)
{
	char	*value;

	value = get_key_value(g_minishell.envp_list, "HOME");
	if (ft_strlen(value))
		swap_pwds(value);
	else
	{
		//ft_printf(STDERR_FILENO, "bash: cd: HOME not set\n");
		write(2, "bash: cd: HOME not set\n", 24);
		return (1);
	}
	return (0);
}
/*
Diese Funktion gibt den Dateityp des angegebenen Pfads zurück.
Überprüft den Dateityp mit Hilfe der stat-Funktion.
Wenn es sich um eine reguläre Datei handelt, wird REG_FILE zurückgegeben.
Wenn es sich um ein Verzeichnis handelt, wird DIR_FILE zurückgegeben.
Andernfalls wird NO_SUCH_FILE zurückgegeben.
*/
int	type_of_file(char *file)
{
	struct stat	file_status;

	if (!file)
		return (NO_SUCH_FILE);
	file_status.st_mode = 0;
	stat(file, &file_status);
	if (S_ISREG(file_status.st_mode))
		return (REG_FILE);
	else if (S_ISDIR(file_status.st_mode))
		return (DIR_FILE);
	return (NO_SUCH_FILE);
}

static void	print_error_cd(t_command cmd, int filetype)
{
	if (filetype == REG_FILE)
	{
		write(STDERR_FILENO,"bash: cd:",9);
		ft_putstr_fd(cmd.args[1], 2);
		write(STDERR_FILENO,": Not a directory\n",18);
	}
	else
	{
		write(STDERR_FILENO,"bash: cd:",9);
		ft_putstr_fd(cmd.args[1], 2);
		write(STDERR_FILENO,": No such file or directory\n",27);
	}
}
/*
Diese Funktion implementiert den Befehl "cd" (change directory) in einer Shell.
Überprüft die Anzahl der Argumente des Befehls.
Wenn es nur ein Argument gibt, ruft change_home auf.
Wenn es mehr als zwei Argumente gibt, wird eine Fehlermeldung für zu viele Argumente ausgegeben.
Andernfalls wird der Dateityp des angegebenen Pfads überprüft.
Wenn es sich um eine reguläre Datei oder eine nicht vorhandene Datei handelt, wird eine entsprechende Fehlermeldung ausgegeben.
Andernfalls wird das Arbeitsverzeichnis gewechselt und der Status auf 0 gesetzt.
Die Umgebungsvariablen werden aktualisiert.
Wenn die Shell im Kindprozessmodus (g_minishell.on_fork) ist, wird die_child aufgerufen, um den Kindprozess zu beenden.
Der Status wird zurückgegeben.
*/
int	ft_cd(t_command cmd)
{
	/*
	int	status;
	int	filetype;

	status = 1;
	if (cmd.number_of_args == 1)
		status = change_home();
	else if (cmd.number_of_args > 2)
		ft_printf(STDERR_FILENO, "bash: cd: too many arguments\n");
	else
	{
		filetype = type_of_file(cmd.args[1]);
		if (filetype == REG_FILE || filetype == NO_SUCH_FILE)
			print_error(cmd, filetype);
		else
		{
			status = 0;
			swap_pwds(cmd.args[1]);
		}
	}
	update_env();
	if (g_minishell.on_fork)
		die_child(0, status);
	return (status);
	*/

int status = 1;

    if (cmd.number_of_args == 1) {
        status = change_home();
    }
    else if (cmd.number_of_args > 2) 
	{
        //ft_printf(STDERR_FILENO, "bash: cd: too many arguments\n");
        write(2, "bash: cd: too many arguments\n", 30);
    }
    else {
        int filetype = type_of_file(cmd.args[1]);
        if (filetype == REG_FILE || filetype == NO_SUCH_FILE) {
            print_error_cd(cmd, filetype);
        }
        else {
            status = 0;
            swap_pwds(cmd.args[1]);
        }
    }

    update_env();

    if (g_minishell.on_fork) {
        die_child(0, status);
    }

    return status;
}


