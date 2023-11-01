/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endProChild.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 19:43:55 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_fd_close(void)
{
	int			i;
	int			size;
	t_command	cmd;

	i = 0;
	size = g_minishell.command_anzahl;
	while (i < size)
	{
		cmd = g_minishell.commands[i];
		if (cmd.eingabe != 0)
			close(cmd.eingabe);
		if (cmd.ausgabe != 1)
			close(cmd.ausgabe);
		if (cmd.pipe[0] != 0)
			close(cmd.pipe[0]);
		if (cmd.pipe[1] != 0)
			close(cmd.pipe[1]);
		i++;
	}
}

void	end_pro_child(int heredoc, int status_code)
{
	if (heredoc)
		close(g_minishell.heredoc.fd);
	else
		child_fd_close();
	end_alles();
	ft_free_matrix((void **)g_minishell.envp);
	ft_free_list(&g_minishell.envp_list);
	rl_clear_history();
	exit(status_code);
}
