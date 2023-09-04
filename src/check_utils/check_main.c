#include "../../inc/minishell.h"
//is_quote
int zitat(char c)
{
    return (c == 39 || c == 34);
}
//is_meta_shar
int special_mark(char c)
{
	if(c == '>')
		return 1;
	else if (c == '<')
		return 1;
	else if (c == '|')
		return 1;
	else
		return 0;
    //return ft_strchr(">|<", c) != NULL;
}

int	checkErrorExistiert(t_command *cmd)
{
	if (g_minishell.heredoc.heredoc_exited != 0 \
		|| cmd->input_fd == -1 || cmd->output_fd == -1)
		return (1);
	return (0);
}

int	checkIsDirectory(const char *path)
{
	/*
	struct stat	file_stat;

	if (!path)
		return (0);
	file_stat.st_mode = 0;
	stat(path, &file_stat);
	return (S_ISDIR(file_stat.st_mode));
	*/
	if (path == NULL) {
        // Wenn der Pfad NULL ist, wird angenommen, dass es sich nicht um ein Verzeichnis handelt.
        return false;
    }

    struct stat file_stat;
    if (stat(path, &file_stat) != 0) {
        // Fehler bei der stat-Funktion, wir gehen davon aus, dass es sich nicht um ein Verzeichnis handelt.
        return false;
    }

    // Prüfen, ob der Dateimodus im file_stat-Objekt auf ein Verzeichnis hinweist.
    return S_ISDIR(file_stat.st_mode);
}