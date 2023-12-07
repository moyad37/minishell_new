/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/07 19:49:47 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init(char **envp)
{
	int	i;

	i = 0;
	g_minishell.status_code = 0;
	i++;
	g_minishell.in_child_process = 0;
	i++;
	g_minishell.envp_list = ev_list_get(envp);
	i++;
	g_minishell.envp = creat_valid_envp();
	i++;
	g_minishell.builtins[0] = ft_echo;
	i++;
	g_minishell.builtins[1] = ft_cd;
	i++;
	g_minishell.builtins[2] = ft_pwd;
	i++;
	g_minishell.builtins[3] = ft_export;
	i++;
	g_minishell.builtins[4] = ft_unset;
	i++;
	g_minishell.builtins[5] = ft_env;
	i++;
	g_minishell.builtins[6] = ft_exit;
	return (++i);
}
