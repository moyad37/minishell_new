#include "../../inc/minishell.h"

static void	init_executor(char **tokens)
{
	init_commands(tokens, 0);
	ft_free_matrix((void **)tokens);
	remove_filename_quotes();
	init_redirects();
	remove_redirects();
	remove_quotes();
	update_number_of_args();
	init_bin_path();
}


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

static void	set_bin(t_command *cmd)
{
	cmd->error = 0;
	if (cmd->args[0] && access(cmd->args[0], F_OK | X_OK) == 0 \
			&& !is_dir(cmd->args[0]))
		cmd->bin_path = ft_strdup(cmd->args[0]);
	else
		cmd->bin_path = get_bin_path(cmd);
	if (cmd->bin_path && cmd->args[0] == NULL)
		cmd->error = 1;
	else if (is_dir(cmd->args[0]) && access(cmd->args[0], F_OK | X_OK) == 0)
		cmd->error = EISDIR;
	else if (ft_strchr(cmd->args[0], 47) && cmd->bin_path == NULL)
		cmd->error = ENOENT;
	else if (cmd->error == 0 && cmd->bin_path == NULL)
		cmd->error = ENOCMD;
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

void	init_commands(char **tokens, int idx)
{
	int		i;
	int		args;
	int		number_of_cmds;

	i = 0;
	if (idx == 0)
	{
		g_minishell.number_of_cmds = count_commands(tokens);
		number_of_cmds = g_minishell.number_of_cmds;
		g_minishell.commands = ft_calloc(sizeof(t_command), number_of_cmds + 1);
	}
	if (tokens[i] == NULL)
		return ;
	while (tokens[i] && ft_strcmp("|", tokens[i]) != 0)
		i++;
	if (tokens[i] && ft_strcmp("|", tokens[i]) == 0)
		i++;
	init_commands(tokens + i, idx + 1);
	args = count_args(tokens);
	g_minishell.commands[idx].number_of_args = args;
	g_minishell.commands[idx].args = ft_calloc(sizeof(char *), args + 1);
	fill_args(tokens, idx);
}
