#include "inc/minishell.h"

t_minishell g_minishell;

static void	print_possible_errors(void)
{
	int			i;
	int			size;
	t_command	cmd;

	i = 0;
	size = g_minishell.number_of_cmds;
	while (i < size && finde_Position_builtin(g_minishell.commands[i].args[0]) == -1)
	{
		cmd = g_minishell.commands[i];
		print_aktuell_err(cmd);
		i++;
	}
}


int	main(int ac, char **av, char **envp)
{
	char *cmd_line;
	char **tokens;
	if (!check_arg(ac, av, envp))
		print_error("arg error, make sure you have like so : './minishell' \n",
				2);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	init_minishell(envp);
	while (1)
	{
		cmd_line = readline("$ ");
		tokens = Start_validiere_und_tokenize_Eingabe(cmd_line);
		if (tokens)
		{
			executor(tokens);
			print_possible_errors();
			ft_free_commands();
		}
	}
}