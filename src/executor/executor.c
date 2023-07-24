#include "../../inc/minishell.h"

void	executor(char **tokens)
{
	int	i;
	int	pid;
	int	status;

	i = -1;
	status = -1;
	init_executor(tokens);
	if (g_minishell.heredoc.heredoc_exited == 1)
	{
		g_minishell.status_code = 130;
		g_minishell.heredoc.heredoc_exited = 0;
		return ;
	}
	if (g_minishell.number_of_cmds > 1)
		while (++i < g_minishell.number_of_cmds)
			pid = handle_exec(i, &g_minishell.commands[i]);
	else
		pid = run_single_cmd(g_minishell.commands[0]);
	if (pid != -1)
		loop_wait(pid, &status);
	g_minishell.on_fork = 0;
}