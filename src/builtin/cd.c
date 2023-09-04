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


void	changeDir(char *new_dir)
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
    char *oldpwd = NULL;
    char *pwd = NULL;

    char *oldpwd_env = getenv("OLDPWD");
    if (oldpwd_env) {
        oldpwd = strdup(oldpwd_env);
        setenv("OLDPWD", getcwd(NULL, 0), 1);
    }

    chdir(new_dir);

    char *pwd_env = getenv("PWD");
    if (pwd_env) {
        pwd = strdup(pwd_env);
        setenv("PWD", getcwd(NULL, 0), 1);
    }

    free(oldpwd);
    free(pwd);

}
/*
Diese Funktion ändert das Arbeitsverzeichnis basierend auf dem Wert der Umgebungsvariablen "HOME".
Ruft changeDir auf und übergibt den Wert von "HOME".
Wenn der Wert von "HOME" leer ist, gibt die Funktion einen Fehler aus und gibt 1 zurück.
*/
int	changeHome(void)
{
    char *home = getenv("HOME");
    if (home) {
        changeDir(home);
        return 0;
    } else {
        write(2, "bash: cd: HOME not set\n", 24);
        return 1;
    }
}
/*
Diese Funktion gibt den Dateityp des angegebenen Pfads zurück.
Überprüft den Dateityp mit Hilfe der stat-Funktion.
Wenn es sich um eine reguläre Datei handelt, wird REG_FILE zurückgegeben.
Wenn es sich um ein Verzeichnis handelt, wird DIR_FILE zurückgegeben.
Andernfalls wird NO_SUCH_FILE zurückgegeben.
*/
int	getFileType(char *file)
{
    struct stat fileStatus;
    if (file && stat(file, &fileStatus) == 0) {
        if (S_ISREG(fileStatus.st_mode)) {
            return 1; // REG_FILE
        } else if (S_ISDIR(fileStatus.st_mode)) {
            return 2; // DIR_FILE
        }
    }
    return 0; // NO_SUCH_FILE
}

void printCdError(char *file, int filetype)
{
    if (filetype == 1) {
        write(STDERR_FILENO, "bash: cd:", 9);
        write(STDERR_FILENO, file, strlen(file));
        write(STDERR_FILENO, ": Not a directory\n", 18);
    } else {
        write(STDERR_FILENO, "bash: cd:", 9);
        write(STDERR_FILENO, file, strlen(file));
        write(STDERR_FILENO, ": No such file or directory\n", 27);
    }
}
/*
Diese Funktion implementiert den Befehl "cd" (change directory) in einer Shell.
Überprüft die Anzahl der Argumente des Befehls.
Wenn es nur ein Argument gibt, ruft changeHome auf.
Wenn es mehr als zwei Argumente gibt, wird eine Fehlermeldung für zu viele Argumente ausgegeben.
Andernfalls wird der Dateityp des angegebenen Pfads überprüft.
Wenn es sich um eine reguläre Datei oder eine nicht vorhandene Datei handelt, wird eine entsprechende Fehlermeldung ausgegeben.
Andernfalls wird das Arbeitsverzeichnis gewechselt und der Status auf 0 gesetzt.
Die Umgebungsvariablen werden aktualisiert.
Wenn die Shell im Kindprozessmodus (g_minishell.on_fork) ist, wird ChildProEnd aufgerufen, um den Kindprozess zu beenden.
Der Status wird zurückgegeben.
*/
int	ft_cd(t_command cmd)
{
	/*
	int	status;
	int	filetype;

	status = 1;
	if (cmd.number_of_args == 1)
		status = changeHome();
	else if (cmd.number_of_args > 2)
		ft_printf(STDERR_FILENO, "bash: cd: too many arguments\n");
	else
	{
		filetype = getFileType(cmd.args[1]);
		if (filetype == REG_FILE || filetype == NO_SUCH_FILE)
			print_error(cmd, filetype);
		else
		{
			status = 0;
			changeDir(cmd.args[1]);
		}
	}
	update_env();
	if (g_minishell.on_fork)
		ChildProEnd(0, status);
	return (status);
	*/

int status = 1;

    if (cmd.number_of_args == 1) {
        status = changeHome();
    } else if (cmd.number_of_args > 2) {
        write(STDERR_FILENO, "bash: cd: too many arguments\n", 30);
    } else {
        int filetype = getFileType(cmd.args[1]);
        if (filetype == 1 || filetype == 0) {
            printCdError(cmd.args[1], filetype);
        } else {
            status = 0;
            changeDir(cmd.args[1]);
        }
    }

    update_env();

    if (g_minishell.on_fork) {
        ChildProEnd(0, status);
    }

    return status;
}


