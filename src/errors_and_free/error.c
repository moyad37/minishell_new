
#include "../../inc/minishell.h"

int print_error(const char *str, int fd)
{
    int i;

    i = 0;
    if(!str)
        return (2);
    while (str[i++])
        write(fd, &str[i], 1);
    return (2);
}

static void	err_on_input_redirect(char *filename)
{
	int	error;

	if (access(filename, F_OK) == -1)
		error = ENOENT;
	else
		error = EACCES;
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(error), 2);
	ft_putstr_fd("\n", 2);
	//ft_printf(STDERR_FILENO, "bash: %s: %s\n", filename, strerror(error));
}

static void	err_on_output_redirect(char *filename)
{
	int	error;

	if (ft_strlen(filename) > 255)
		error = ENAMETOOLONG;
	else
		error = EACCES;
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(error), 2);
	ft_putstr_fd("\n", 2);	
	//ft_printf(STDERR_FILENO, "bash: %s: %s\n", filename, strerror(error));
}

void	handle_error(t_command *cmd, char *filename)
{
	if (cmd->input_fd == -1)
		err_on_input_redirect(filename);
	else if (cmd->output_fd == -1)
		err_on_output_redirect(filename);
}