#include "../../inc/minishell.h"


static void	swap_fd_input(t_command *command, int new_fd)
{
	if (command->input_fd != 0)
		close(command->input_fd);
	command->input_fd = new_fd;
}

static void	swap_fd_output(t_command *command, int new_fd)
{
	if (command->output_fd != 1)
		close(command->output_fd);
	command->output_fd = new_fd;
}

void	swap_stream_fd(char *stream, t_command *command, int new_fd)
{
	if (ft_strcmp(stream, "input") == 0)
		swap_fd_input(command, new_fd);
	else
		swap_fd_output(command, new_fd);
}