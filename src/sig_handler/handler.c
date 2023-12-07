/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/07 19:46:15 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Der Code definiert eine Funktion handler, die auf das Abbruchsignal SIGINT reagiert, 
indem sie eine neue Zeile hinzufügt und die Eingabezeile löscht, um die Benutzerinteraktion 
in einer Shell zu erleichtern. In einem Kindprozess wird nur eine neue Zeile hinzugefügt.
*/
void	handl_sig(int signal)
{
	if (signal == SIGINT && !g_minishell.in_child_process)
	{
		g_minishell.status_code = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGINT && g_minishell.in_child_process == 1)
	{
		if(g_minishell.shell_lvl < 2)
			write(STDOUT_FILENO, "\n", 1);
	}
}

void	wait_sig(void)
{
	signal(SIGINT, handl_sig);
	signal(SIGQUIT, SIG_IGN);
}