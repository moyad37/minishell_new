/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/07 19:48:46 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include "./src/libft/libft.h"

t_minishell	g_minishell;

char	*first_read(char *cmd)
{
	cmd = readline("$ ");
	if(!cmd)
		return (NULL);
	return (cmd);
}

int check_arg(int ac, char **av, char **envp)
{
    (void)envp;
    if(ac != 1)
        return 0;
    if (av[0][0] != 46)
        return 0;
    if(!av)
        return 0;
    return 1;
}

static void	shell_lvl_plus(void)
{
	char *c;
	char *itoa;

	
	c = get_key_value(g_minishell.envp_list, "SHLVL");
	itoa = ft_itoa(ft_atoi(c) + 1);
	g_minishell.shell_lvl = (ft_atoi(c) + 1);
	change_value_from_key(&g_minishell.envp_list, "SHLVL", itoa);
	free(itoa);
	update_env();
}

int	main(int ac, char **av, char **envp)
{
	char	*cmd;
	char	**command_list;

	cmd = NULL;
	if (!check_arg(ac, av, envp))
	{
		return (p_fd(2, "arg error, make sure you have like so : './minishell' \n"), 0);
	}
	wait_sig();
	if(init(envp) != 11)
		return (0);
	shell_lvl_plus();
	while (1)
	{
		cmd = first_read(cmd);
		if(cmd == NULL)
			ft_destroy();
		command_list = check_commands(cmd);
		if (command_list)
		{
			run_command(command_list, -1, -1);
		}
	}
	return (0);
}
