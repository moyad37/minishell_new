/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 18:52:09 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"


static void	err_on_input_redirect(char *filename)
{
	int	error;

	if (access(filename, F_OK) == -1)
		error = ENOENT;
	else
		error = EACCES;
	p_fd(STDERR_FILENO, "bash: %s: %s\n", filename, strerror(error));
}

static void	err_on_output_redirect(char *filename)
{
	int	error;

	if (ft_strlen(filename) > 255)
		error = ENAMETOOLONG;
	else
		error = EACCES;
	p_fd(STDERR_FILENO, "bash: %s: %s\n", filename, strerror(error));
}

void	handle_error(t_command *cmd, char *filename)
{
	if (cmd->eingabe == -1)
		err_on_input_redirect(filename);
	else if (cmd->ausgabe == -1)
		err_on_output_redirect(filename);
}

