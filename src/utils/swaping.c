/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swaping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/12 18:24:47 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Nimmt einen Befehlszeiger (command) und einen neuen Dateideskriptor
(new_fd) als Parameter.
Schließt den aktuellen Eingabedeskriptor des Befehls und setzt ihn
auf den neuen Dateideskriptor.
*/
static void	swap_fd_input(t_command *command, int new_fd)
{
	if (command->eingabe != 0)
		close(command->eingabe);
	command->eingabe = new_fd;
}
/*
Nimmt einen Befehlszeiger (command) und einen neuen Dateideskriptor
(new_fd) als Parameter.
Schließt den aktuellen Ausgabedeskriptor des Befehls und setzt ihn 
auf den neuen Dateideskriptor.
*/

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
