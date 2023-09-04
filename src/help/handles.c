#include "../../inc/minishell.h"


static void	manageCommandDescriptors(t_command *prev, t_command *curr, t_command *next)
{
	if (!prev)
		dup2(curr->input_fd, STDIN_FILENO);
	else
	{
		if (curr->input_fd == STDIN_FILENO)
			dup2(prev->pipe[READ_END], STDIN_FILENO);
		else
			dup2(curr->input_fd, STDIN_FILENO);
	}
	if (!next)
		dup2(curr->output_fd, STDOUT_FILENO);
	else
	{
		if (curr->output_fd == STDOUT_FILENO)
			dup2(curr->pipe[WR_END], STDOUT_FILENO);
		else
			dup2(curr->output_fd, STDOUT_FILENO);
	}
}

static int	executeCommandSequence(t_command *prev, t_command *curr, t_command *next)
{
	int	pid;
	int	builtin_pos;

	if (next)
		pipe(curr->pipe);
	pid = fork();
	g_minishell.on_fork = 1;
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (curr->input_fd == -1 || curr->output_fd == -1)
			ChildProEnd(0, 1);
		builtin_pos = finde_Position_builtin(curr->args[0]);
		if (builtin_pos != -1)
			stert_builtin(*curr, g_minishell.builtins[builtin_pos]);
		if (curr->bin_path && curr->args[0])
		{
			manageCommandDescriptors(prev, curr, next);
			cleanupChild();
			execve(curr->bin_path, curr->args, g_minishell.envp);
		}
		ChildProEnd(0, curr->error);
	}
	return (pid);
}

int	runPipedCommand(int idx, t_command *curr)
{
	int			pid;
	t_command	prev;
	t_command	next;

	if (idx == 0)
	{
		next = g_minishell.commands[idx + 1];
		pid = executeCommandSequence(NULL, curr, &next);
		close(g_minishell.commands[idx].pipe[WR_END]);
	}
	else if (idx == g_minishell.number_of_cmds - 1)
	{
		prev = g_minishell.commands[idx - 1];
		pid = executeCommandSequence(&prev, curr, NULL);
		close(g_minishell.commands[idx - 1].pipe[READ_END]);
	}
	else
	{
		next = g_minishell.commands[idx + 1];
		prev = g_minishell.commands[idx - 1];
		pid = executeCommandSequence(&prev, curr, &next);
		close(prev.pipe[READ_END]);
		close(curr->pipe[WR_END]);
	}
	return (pid);
}
