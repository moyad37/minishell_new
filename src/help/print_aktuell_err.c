#include "../../inc/minishell.h"

void	gib_code_status(t_command cmd)
{
	if (g_minishell.status_code == 0)
		return ;
	if (checkIsDirectory(cmd.args[0]) && access(cmd.args[0], F_OK | X_OK) == 0 \
			&& ft_strchr(cmd.args[0], 47))
		g_minishell.status_code = 126;
	else if (ft_strchr(cmd.args[0], 47) && cmd.bin_path == NULL \
			&& access(cmd.args[0], F_OK) == -1)
		g_minishell.status_code = 127;
	else if (cmd.bin_path == NULL && cmd.args[0] \
			&& access(cmd.args[0], X_OK) == -1 && ft_strchr(cmd.args[0], 47))
		g_minishell.status_code = 126;
	else if (cmd.bin_path == NULL && cmd.args[0])
		g_minishell.status_code = 127;
}


void    print_aktuell_err(t_command cmd)
{
	if (checkIsDirectory(cmd.args[0]) && access(cmd.args[0], F_OK | X_OK) == 0 \
			&& ft_strchr(cmd.args[0], 47))
		ft_printf2(STDERR_FILENO, "bash: %s: Is a directory\n", cmd.args[0]);
	else if (ft_strchr(cmd.args[0], 47) && cmd.bin_path == NULL \
			&& access(cmd.args[0], F_OK) == -1)
		ft_printf2(2, "bash: %s: No such file or directory\n", cmd.args[0]);
	else if (cmd.bin_path == NULL && cmd.args[0] \
			&& access(cmd.args[0], X_OK) == -1 && ft_strchr(cmd.args[0], 47))
		ft_printf2(STDERR_FILENO, "bash: %s: Permission denied\n", cmd.args[0]);
	else if (cmd.bin_path == NULL && cmd.args[0])
		ft_printf2(STDERR_FILENO, "%s: command not found\n", cmd.args[0]);
	gib_code_status(cmd);
}
