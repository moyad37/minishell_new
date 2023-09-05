#include "../../inc/minishell.h"
//loop_wait
static void	loopForNext(int pid, int *status)
{
	int	i;
	int	size;

	i = 0;
	size = g_minishell.number_of_cmds;
	waitpid(pid, status, 0);
	while (i < size - 1)
	{
		wait(NULL);
		i++;
	}
	if (WIFEXITED(*status))
		g_minishell.status_code = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		g_minishell.status_code = 128 + WTERMSIG(*status);
}
//run_single_cmd
static int	signalCommandOn(t_command cmd)
{
	int	pid;

	if (finde_Position_builtin(cmd.args[0]) != -1)
	{
		stert_builtin(cmd, g_minishell.builtins[finde_Position_builtin(cmd.args[0])]);
		return (-1);
	}
	pid = fork();
	g_minishell.on_fork = 1;
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (cmd.input_fd == -1 || cmd.output_fd == -1)
			ChildProEnd(0, 1);
		if (cmd.error && finde_Position_builtin(cmd.args[0]) == -1)
			ChildProEnd(0, cmd.error);
		if (cmd.bin_path && cmd.args[0])
		{
			redirect_standard_streams_dups(cmd);
			cleanupChild();
			execve(cmd.bin_path, cmd.args, g_minishell.envp);
		}
		ChildProEnd(0, cmd.error);
	}
	return (pid);
}
//init_executor
static void	initExecutor(char **tokens)
{
	initCommands(tokens, 0);
	FreeMatrix((void **)tokens);
	deleteQu();
	configure_cmd_fds();
	deleteRedirects();
	deleteQuote();
	update_args_count();
	initBinWay();
}

void	executor(char **tokens)
{
	int	i;
	int	pid;
	int	status;

	i = -1;
	status = -1;
	initExecutor(tokens);
	if (g_minishell.heredoc.heredoc_exited == 1)
	{
		g_minishell.status_code = 130;
		g_minishell.heredoc.heredoc_exited = 0;
		return ;
	}
	if (g_minishell.number_of_cmds > 1)
		while (++i < g_minishell.number_of_cmds)
			pid = runPipedCommand(i, &g_minishell.commands[i]);
	else
		pid = signalCommandOn(g_minishell.commands[0]);
	if (pid != -1)
		loopForNext(pid, &status);
	g_minishell.on_fork = 0;
}

