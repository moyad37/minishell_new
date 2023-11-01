/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 19:45:47 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_command cmd)
{
	int	out;

	out = 1;
	check_output_with_pipe(cmd, &out);
	if (cmd.args[0])
		ft_print_matrix_fd(g_minishell.envp, out);
	if (g_minishell.in_child_process)
		end_pro_child(0, 0);
	return (0);
}
