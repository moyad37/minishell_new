#include "../../inc/minishell.h"

void	remove_redirects(void)
{
	int	i;
	int	args;

	i = 0;
	args = g_minishell.number_of_cmds;
	while (i < args)
	{
		remove_redirect(&g_minishell.commands[i].args);
		i++;
	}
}

static void	remove_redirect(char ***command_args)
{
	int		tokens_amount;
	char	**new_tokens;

	tokens_amount = exclude_redirects(*command_args);
	new_tokens = ft_calloc(sizeof(char *), tokens_amount + 1);
	copy_tokens(new_tokens, *command_args);
	ft_free_matrix((void **)*command_args);
	*command_args = new_tokens;
}

static int	exclude_redirects(char **tokens)
{
	int	i;
	int	mem_to_alloc;

	i = 0;
	mem_to_alloc = 0;
	while (tokens[i])
	{
		if (is_redirect(tokens[i]))
			i++;
		else
			mem_to_alloc++;
		i++;
	}
	return (mem_to_alloc);
}


static void	fill_fds(t_command *cmd)
{
	int	i;

	i = 0;
	cmd->input_fd = 0;
	cmd->output_fd = 1;
	while (cmd->args[i])
	{
		if (is_input_redirect(cmd->args[i]))
			set_input_fd(cmd, cmd->args[i], cmd->args[i + 1]);
		else if (is_output_redirect(cmd->args[i]))
			set_output_fd(cmd, cmd->args[i], cmd->args[i + 1]);
		if (has_error(cmd))
		{
			handle_error(cmd, cmd->args[i + 1]);
			return ;
		}
		if (is_redirect(cmd->args[i]))
			i++;
		i++;
	}
}

void	init_redirects(void)
{
	int	i;
	int	args;

	i = 0;
	args = g_minishell.number_of_cmds;
	while (i < args && !g_minishell.heredoc.heredoc_exited)
	{
		fill_fds(&g_minishell.commands[i]);
		i++;
	}
}
