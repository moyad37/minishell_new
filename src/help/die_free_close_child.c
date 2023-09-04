#include "../../inc/minishell.h"

void	ChildProEnd(int heredoc, int exit_code)
{
	if (heredoc)
		close(g_minishell.heredoc.fd);
	else
		cleanupChild();
	ft_free_commands();
	ft_free_matrix((void **)g_minishell.envp);
	ft_free_list(&g_minishell.envp_list);
	rl_clear_history();
	exit(exit_code);
}

void	ft_free_commands(void)
{
	int	i;
	int	args;

	i = 0;
	args = g_minishell.number_of_cmds;
	cleanup_command_fds();
	while (i < args)
	{
		ft_free_matrix((void **)g_minishell.commands[i].args);
		ft_free((void *)g_minishell.commands[i].bin_path);
		i++;
	}
	free(g_minishell.commands);
	g_minishell.commands = NULL;
}


void	cleanupChild(void)
{
	int			i;
	int			size;
	t_command	cmd;

	i = 0;
	size = g_minishell.number_of_cmds;
	while (i < size)
	{
		cmd = g_minishell.commands[i];
		if (cmd.input_fd != 0)
			close(cmd.input_fd);
		if (cmd.output_fd != 1)
			close(cmd.output_fd);
		if (cmd.pipe[0] != 0)
			close(cmd.pipe[0]);
		if (cmd.pipe[1] != 0)
			close(cmd.pipe[1]);
		i++;
	}
}

void	cleanup_command_fds(void)
{
	int	i;
	int	commands_size;

	i = 0;
	commands_size = g_minishell.number_of_cmds;
	if (g_minishell.commands == NULL)
		return ;
	while (i < commands_size)
	{
		if (g_minishell.commands[i].input_fd != 0)
			close(g_minishell.commands[i].input_fd);
		if (g_minishell.commands[i].output_fd != 1)
			close(g_minishell.commands[i].output_fd);
		i++;
	}
}

void	die(void)
{
	rl_clear_history();
	ft_free_list(&g_minishell.envp_list);
	ft_free_matrix((void **)g_minishell.envp);
	cleanup_command_fds();
	unlink(TMPFILE);
	write(1, "exit\n", 5);
	exit(0);
}