#include "../../inc/minishell.h"


static int	has_non_numeric_char(char *first_arg)
{
	while (first_arg && *first_arg)
	{
		if (!ft_isdigit(*first_arg) && *first_arg != '-' && *first_arg != '+')
			return (1);
		first_arg++;
	}
	return (0);
}

static int	out_of_range(char *nptr)
{
	int			nptr_len;
	long int	nbr;

	nptr_len = ft_strlen(nptr);
	nbr = ft_latoi(nptr);
	if (nptr_len > 1 && nbr == 0)
		return (1);
	return (0);
}

static int	get_exit_code(t_command cmd)
{
	if (out_of_range(cmd.args[1]))
	{
		ft_printf2(STDERR_FILENO, \
				"bash: exit: %s: numeric argument required\n", cmd.args[1]);
		return (2);
	}
	else
		return (ft_latoi(cmd.args[1]));
}



/*

Diese Funktion implementiert den Befehl "exit" in einer Shell. Wenn kein Argument
 angegeben ist, wird die Ausgabe "exit" gemacht und der Kindprozess beendet. 
 Andernfalls wird das erste Argument in eine Ganzzahl umgewandelt und als exit_code 
 gespeichert. Es werden verschiedene Überprüfungen durchgeführt, um sicherzustellen,
  dass das Argument gültig ist. Danach wird die Ausgabe "exit" gemacht und der Kindprozess 
  mit dem exit_code beendet. Der Rückgabewert 0 gibt an, dass der Befehl erfolgreich ausgeführt wurde.
*/
// void print_error_exit(int fd, char *str)
// {
// 	ft_putstr_fd("bash: exit: ",2);
// 	ft_putstr_fd(str, fd);
// 	ft_putstr_fd(": numeric argument required\n",2);
// }

int	ft_exit(t_command cmd)
{

	long int	exit_code;

	exit_code = 0;
	if (cmd.args[1] == NULL)
		ChildProEnd(0, exit_code);
	if (has_non_numeric_char(cmd.args[1]))
	{
		ft_printf2(STDERR_FILENO, \
			"bash: exit: %s: numeric argument required\n", cmd.args[1]);
		exit_code = 2;
	}
	else if (cmd.number_of_args > 2)
	{
		ft_printf2(STDERR_FILENO, "bash: exit: too many arguments\n");
		exit_code = 1;
	}
	else
		exit_code = get_exit_code(cmd);
	ft_putstr_fd("exit\n", STDIN_FILENO);
	ChildProEnd(0, exit_code);
	return (0);


	/*
	long int exit_code;

	if (cmd.args[1] == NULL)
	{
		ft_putstr_fd("exit\n", STDIN_FILENO);
		ChildProEnd(0, 0);
	}
	else
	{
		exit_code = ft_latoi(cmd.args[1]);
		if (exit_code == 0 && ft_strlen(cmd.args[1]) > 1)
		{
			//print_error_exit(STDERR_FILENO, cmd.args[1]);
			ft_printf2(STDERR_FILENO, "bash: exit: %s: numeric argument required\n", cmd.args[1]);
			exit_code = 2;
		}
		else if (cmd.number_of_args > 2)
		{
			write(STDERR_FILENO, "bash: exit: too many arguments\n", 31);
			exit_code = 1;
		}
		ft_putstr_fd("exit\n", STDIN_FILENO);
		ChildProEnd(0, exit_code);
	}
	return 0;
	*/
}

