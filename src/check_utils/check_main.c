#include "../../inc/minishell.h"

int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

int is_meta_char(char c)
{
    return strchr(">|<", c) != NULL;
}

int	has_error(t_command *cmd)
{
	if (g_minishell.heredoc.heredoc_exited != 0 \
		|| cmd->input_fd == -1 || cmd->output_fd == -1)
		return (1);
	return (0);
}

int	is_dir(const char *path)
{
	struct stat	file_stat;

	if (!path)
		return (0);
	file_stat.st_mode = 0;
	stat(path, &file_stat);
	return (S_ISDIR(file_stat.st_mode));
}