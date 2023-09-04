#include "../../inc/minishell.h"
// Original: void swap_pwds(char *new_dir)
// Änderung des aktuellen Verzeichnisses
void changeDir(char *new_dir)
{
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

// Original: int change_home(void)
// Änderung des Verzeichnisses zu Hause
int changeHome(void)
{
    const char *home = getenv("HOME");
    if (home) {
        changeDir(home);
        return 0;
    } else {
        write(2, "bash: cd: HOME not set\n", 24);
        return 1;
    }
}

// Original: int type_of_file(char *file)
// Bestimmung des Dateityps
int getFileType(char *file)
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

// Original: static void print_error_cd(t_command cmd, int filetype)
// Fehlermeldung bei 'cd'
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

// Original: int ft_cd(t_command cmd)
// 'cd' Befehlsausführung
int cdCommand(t_command cmd) {
    int status = 1;

    if (cmd.number_of_args == 1) {
        status = changeHome();
    } else if (cmd.number_of_args > 2) {
        write(STDERR_FILENO, "bash: cd: too many arguments\n", 30);
    } else {
        int filetype = typeOfFile(cmd.args[1]);
        if (filetype == 1 || filetype == 0) {
            printCdError(cmd.args[1], filetype);
        } else {
            status = 0;
            changeDir(cmd.args[1]);
        }
    }

    updateEnv();

    if (g_minishell.on_fork) {
        dieChild(0, status);
    }

    return status;
}