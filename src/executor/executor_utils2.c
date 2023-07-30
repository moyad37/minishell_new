#include "../../inc/minishell.h"

void	init_bin_path(void)
{
	int	i;
	int	args;

	i = 0;
	args = g_minishell.number_of_cmds;
	while (i < args)
	{
		set_bin(&g_minishell.commands[i]);
		i++;
	}
}

static void	fill_args(char **tokens, int idx)
{
	int	i;
	int	args;

	i = 0;
	args = g_minishell.commands[idx].number_of_args;
	while (i < args)
	{
		g_minishell.commands[idx].args[i] = ft_strdup(tokens[i]);
		i++;
	}
}

void	remove_filename_quotes(void)
{
	int			i;
	int			j;
	t_command	*cmd;
	char		**subtokens;

	i = 0;
	while (i < g_minishell.number_of_cmds)
	{
		j = 0;
		cmd = &g_minishell.commands[i];
		while (cmd->args[j])
		{
			if (is_redirect(cmd->args[j]))
			{
				subtokens = get_subtokens(cmd->args[j + 1], 0);
				clear_subtokens(subtokens);
				free(cmd->args[j + 1]);
				cmd->args[++j] = concat_subtokens(subtokens);
				free(subtokens);
			}
			j++;
		}
		i++;
	}
}

void	remove_quotes(void)
{
	int	i;
	int	args;

	i = 0;
	args = g_minishell.number_of_cmds;
	while (i < args)
	{
		erase_empty_quotes_and_ext_quotes(g_minishell.commands[i].args);
		i++;
	}
}

static void	erase_empty_quotes_and_ext_quotes(char **tokens)
{
	int		i;
	char	**subtokens;

	i = 0;
	while (tokens[i] != NULL)
	{
		subtokens = get_subtokens(tokens[i], 0);
		clear_subtokens(subtokens);
		free(tokens[i]);
		tokens[i] = concat_subtokens(subtokens);
		free(subtokens);
		i++;
	}
}
