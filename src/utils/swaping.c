/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swaping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 18:52:07 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"


static void	swap_fd_input(t_command *command, int new_fd)
{
	if (command->eingabe != 0)
		close(command->eingabe);
	command->eingabe = new_fd;
}

static void	swap_fd_output(t_command *command, int new_fd)
{
	if (command->ausgabe != 1)
		close(command->ausgabe);
	command->ausgabe = new_fd;
}

void	swap_stream_fd(char *stream, t_command *command, int new_fd)
{
	if (ft_strcmp(stream, "input") == 0)
		swap_fd_input(command, new_fd);
	else
		swap_fd_output(command, new_fd);
}
