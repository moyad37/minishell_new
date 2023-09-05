
#include "../../inc/minishell.h"

static void	konfiguriere_ausgabeumleitung(t_command *cmd, char *redirect, char *filename)
{
	int	flags;

	if (ft_strcmp(">", redirect) == 0)
	{
		flags = O_CREAT | O_WRONLY | O_TRUNC;
		update_stream_fd("output", cmd, open(filename, flags, 0644));
	}
	else
	{
		flags = O_CREAT | O_WRONLY | O_APPEND;
		update_stream_fd("output", cmd, open(filename, flags, 0644));
	}
}

static void	konfiguriere_eingabeumleitung(t_command *cmd, char *redirect, char *filename)
{
	char	*delim;

	if (ft_strcmp("<", redirect) == 0)
		update_stream_fd("input", cmd, open(filename, O_RDONLY));
	else
	{
		delim = filename;
		g_minishell.heredoc.heredoc_exited = heredoc(cmd, delim);
	}
}

static void	konfiguriere_befehlsdateideskriptoren(t_command *cmd)
{
	int	i;

	i = 0;
	cmd->input_fd = 0;
	cmd->output_fd = 1;
	while (cmd->args[i])
	{
		if (is_input_redirect(cmd->args[i]))
			konfiguriere_eingabeumleitung(cmd, cmd->args[i], cmd->args[i + 1]);
		else if (is_output_redirect(cmd->args[i]))
			konfiguriere_ausgabeumleitung(cmd, cmd->args[i], cmd->args[i + 1]);
		if (checkErrorExistiert(cmd))
		{
			handle_error(cmd, cmd->args[i + 1]);
			return ;
		}
		if (is_redirect(cmd->args[i]))
			i++;
		i++;
	}
}

void	configure_cmd_fds(void)
{
	int	i;
	int	args;

	i = 0;
	args = g_minishell.number_of_cmds;
	while (i < args && !g_minishell.heredoc.heredoc_exited)
	{
		konfiguriere_befehlsdateideskriptoren(&g_minishell.commands[i]);
		i++;
	}
}
