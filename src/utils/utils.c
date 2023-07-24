#include "../../inc/minishell.h"

static void	copy_tokens(char **new, char **copy)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (copy[i])
	{
		if (is_redirect(copy[i]))
			i++;
		else
			new[j++] = ft_strdup(copy[i]);
		i++;
	}
}

int	count_args(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] && ft_strcmp("|", tokens[i]) != 0)
		i++;
	return (i);
}


void	update_number_of_args(void)
{
	int			i;
	int			size;
	t_command	*cmd;

	i = 0;
	size = g_minishell.number_of_cmds;
	while (i < size)
	{
		cmd = &g_minishell.commands[i];
		cmd->number_of_args = count_args(cmd->args);
		i++;
	}
}

void	make_dups(t_command cmd)
{
	dup2(cmd.input_fd, 0);
	dup2(cmd.output_fd, 1);
}
