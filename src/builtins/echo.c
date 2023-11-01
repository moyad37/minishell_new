/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 20:19:51 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	if_n(char *dash_n)
{
	int	i;

	i = 0;
	if (dash_n[i] == '-')
		i++;
	else
		return (0);
	while (dash_n[i] == 'n')
		i++;
	if (dash_n[i] == '\0')
		return (1);
	return (0);
}

static void	print_after_check(int size, char **args, int out_fd)
{
	int	i;

	i = 1;
	if (if_n(args[1]))
		i++;
	while (i < size - 1)
	{
		ft_putstr_fd(args[i], out_fd);
		ft_putstr_fd(" ", out_fd);
		i++;
	}
	if (args[i])
		ft_putstr_fd(args[i], out_fd);
}

void printCommand(t_command cmd)
{
    printf("pipe: [%d, %d]\n", cmd.pipe[0], cmd.pipe[1]);
    printf("arg_counter: %d\n", cmd.arg_counter);
    printf("input_fd: %d\n", cmd.eingabe);
    printf("output_fd: %d\n", cmd.ausgabe);
    printf("error: %d\n", cmd.error);
    printf("executable_path: %s\n", cmd.executable_path);
    printf("args:\n");
    for (int i = 0; i < cmd.arg_counter; i++)
	{
        printf("  args[%d]: %s\n", i, cmd.args[i]);
    }
}


/*
Die ft_echo-Funktion behandelt den echo-Befehl in einer Shell. Sie überprüft die Argumente,
gibt Text aus und berücksichtigt den -n-Schalter. Je nach Situation gibt sie einen Zeilenumbruch
aus und kümmert sich um die Ein- und Ausgabeverwaltung in einem Kindprozess oder in der Haupt-Shell.
*/
int	ft_echo(t_command cmd)
{
	int	comparison;
	int	out;

	out = 1;
	//printCommand(cmd);
	check_output_with_pipe(cmd, &out);
	comparison = 1;
	if (g_minishell.in_child_process && (cmd.eingabe == -1 || cmd.ausgabe == -1))
		end_pro_child(0, 1);
	if (!g_minishell.in_child_process && (cmd.eingabe == -1 || cmd.ausgabe == -1))
		return (1);
	if (cmd.arg_counter < 2)
		ft_putstr_fd("\n", out);
	else
	{
		comparison = if_n(cmd.args[1]);
		print_after_check(cmd.arg_counter, cmd.args, out);
		if (comparison == 0)
			ft_putstr_fd("\n", out);
	}
	if (g_minishell.in_child_process)
		end_pro_child(0, 0);
	return (0);
}


