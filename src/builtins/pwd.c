/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 19:45:53 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_command cmd)
{
	char	*cwd;
	int		out;

	out = 1;
	check_output_with_pipe(cmd, &out);
	cwd = getcwd(NULL, 0);
	if (cmd.args[0])
		p_fd(out, "%s\n", cwd);
	ft_free(cwd);
	if (g_minishell.in_child_process)
		end_pro_child(0, 0);
	return (0);
}
