#include "../../inc/minishell.h"

int	get_builtin_pos(char *str)
{
	if (!str)
		return (-1);
	if (ft_strcmp(str, "echo") == 0)
		return (0);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (2);
	else if (ft_strcmp(str, "export") == 0)
		return (3);
	else if (ft_strcmp(str, "unset") == 0)
		return (4);
	else if (ft_strcmp(str, "env") == 0)
		return (5);
	else if (ft_strcmp(str, "exit") == 0)
		return (6);
	return (-1);
}


void	handle_input(t_command cmd, int *fd)
{
	if (cmd.input_fd != STDIN_FILENO)
		*fd = cmd.input_fd;
	else if (cmd.pipe[0] != 0)
		*fd = cmd.pipe[0];
}

void	handle_output(t_command cmd, int *fd)
{
	if (cmd.output_fd != STDOUT_FILENO)
		*fd = cmd.output_fd;
	else if (cmd.pipe[1] != 0)
		*fd = cmd.pipe[1];
}

void	run_builtin(t_command cmd, int (*builtin)(t_command cmd))
{
	if (g_minishell.on_fork)
		builtin(cmd);
	else
	{
		if (ft_strcmp(cmd.args[0], "exit") == 0)
			g_minishell.status_code = builtin(cmd);
		g_minishell.status_code = builtin(cmd);
	}
}

void	update_env(void)
{
	ft_free_matrix((void **)g_minishell.envp);
	g_minishell.envp = get_envp();
}