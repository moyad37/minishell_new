#include "../../inc/minishell.h"


static void	update_input_fd(t_command *command, int new_fd)
{
	if (command->input_fd != 0)
		close(command->input_fd);
	command->input_fd = new_fd;
}

static void	update_output_fd(t_command *command, int new_fd)
{
	if (command->output_fd != 1)
		close(command->output_fd);
	command->output_fd = new_fd;
}

void	update_stream_fd(char *stream, t_command *command, int new_fd)
{
	if (ft_strcmp(stream, "input") == 0)
		update_input_fd(command, new_fd);
	else
		update_output_fd(command, new_fd);
}