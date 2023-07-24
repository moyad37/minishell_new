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

static char	**get_path_dirs(void)
{
	int		i;
	char	*path;
	char	**path_dirs;

	i = 0;
	path = get_key_value(g_minishell.envp_list, "PATH");
	path_dirs = ft_split_old(path, ':');
	while (path_dirs[i])
	{
		append(&path_dirs[i], ft_strdup("/"));
		i++;
	}
	return (path_dirs);
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
