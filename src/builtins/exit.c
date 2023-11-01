/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 19:42:25 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_nur_num(char *first_arg)
{
	while (first_arg && *first_arg)
	{
		if (!ft_isdigit(*first_arg) && *first_arg != '-' && *first_arg != '+')
			return (1);
		first_arg++;
	}
	return (0);
}

static int	mehr_als_valid(char *nptr)
{
	int			nptr_len;
	long int	nbr;

	nptr_len = ft_strlen(nptr);
	nbr = ft_latoi(nptr);
	if (nptr_len > 1 && nbr == 0)
		return (1);
	return (0);
}

static int	else_status_code_num(t_command cmd)
{
	if (mehr_als_valid(cmd.args[1]))
	{
		p_fd(STDERR_FILENO, \
				"bash: exit: %s: numeric argument required\n", cmd.args[1]);
		return (2);
	}
	else
		return (ft_latoi(cmd.args[1]));
}

int	ft_exit(t_command cmd)
{
	long int	status_code;

	status_code = 0;
	if (cmd.args[1] == NULL)
		end_pro_child(0, status_code);
	if (check_nur_num(cmd.args[1]))
	{
		p_fd(STDERR_FILENO, \
			"bash: exit: %s: numeric argument required\n", cmd.args[1]);
		status_code = 2;
	}
	else if (cmd.arg_counter > 2)
	{
		p_fd(STDERR_FILENO, "bash: exit: too many arguments\n");
		status_code = 1;
	}
	else
		status_code = else_status_code_num(cmd);
	ft_putstr_fd("exit\n", STDIN_FILENO);
	end_pro_child(0, status_code);
	return (0);
}
