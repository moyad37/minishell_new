/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/12 18:29:55 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	err_on_input_redirect(char *filename)
{
	int	error;

	if (access(filename, F_OK) == -1)
		error = 2;
	else
		error = 13;
	p_fd(STDERR_FILENO, "bash: %s: %s\n", filename, strerror(error));
}

static void	err_on_output_redirect(char *filename)
{
	int	error;

	if (ft_strlen(filename) > 255)
		error = 36;
	else
		error = 13;
	p_fd(STDERR_FILENO, "bash: %s: %s\n", filename, strerror(error));
}

void	handle_error(t_command *cmd, char *filename)
{
	if (cmd->eingabe == -1)
		err_on_input_redirect(filename);
	else if (cmd->ausgabe == -1)
		err_on_output_redirect(filename);
}
