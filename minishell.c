/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/11/10 14:11:57 by mmanssou         ###   ########.fr       */
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

// static void	check_error(void)
// {
// 	int			i;
// 	int			size;
// 	t_command	cmd;

// 	i = 0;
// 	size = g_minishell.command_anzahl;
// 	while (i < size && get_befehl(g_minishell.commands[i].args[0]) == -1)
// 	{
// 		cmd = g_minishell.commands[i];
// 		print_error(cmd);
// 		i++;
// 	}
// }

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
	//t_node	*tmp;

	//tmp = g_minishell.envp_list;
	//printf("env_line = %s   key = %s   val = %s \n\n", g_minishell.envp_list->env_line, g_minishell.envp_list->key, g_minishell.envp_list->value);
	//printf("--------------------------------------------------------------------------------------\n");
	c = get_key_value(g_minishell.envp_list, "SHLVL");
	//printf("c = %s\n",c);
	//printf("i = %d\n",i);
	//printf("i = %d\n",i);
	//g_minishell.envp_list->value = ft_itoa(i);
	g_minishell.shell_lvl = (ft_atoi(c) + 1);
	change_value_from_key(&g_minishell.envp_list, "SHLVL", ft_itoa(ft_atoi(c) + 1));
	//printf("g_minishell.envp_list->value = %s\n",get_key_value(g_minishell.envp_list, "SHLVL"));
	
	update_env();
	//printf("g_minishell.envp_list->value = %s\n",get_key_value(g_minishell.envp_list, "SHLVL"));

	// int x = 0;
	// while(envp[x++])
	// 	printf("envp %d = %s\n\n----------\n\n", x, envp[x]);
	// return (envp);
}

// static void	check_error(void)
// {
// 	int			i;
// 	int			size;
// 	t_command	cmd;

// 	i = 0;
// 	size = g_minishell.command_anzahl;
// 	while (i < size && get_befehl(g_minishell.commands[i].args[0]) == -1)
// 	{
// 		cmd = g_minishell.commands[i];
// 		print_error(cmd);
// 		i++;
// 	}
// }

int	main(int ac, char **av, char **envp)
{
	char	*cmd;
	char	**command_list;

	// if (ac != 1 && !av)
	// 	return (0);
	cmd = NULL;
	if (!check_arg(ac, av, envp))
	{
		p_fd(2, "arg error, make sure you have like so : './minishell' \n");
		return (0);
	}
	wait_sig();
	// signal(SIGINT, handl_sig);
	// signal(SIGQUIT, SIG_IGN);
	if(init(envp) != 11)
		return (0);
	shell_lvl_plus();
	while (1)
	{
		cmd = first_read(cmd);
		if(cmd == NULL)
			ft_destroy();
		//cmd = readline("$ ");
		command_list = check_commands(cmd);
		//if(command_list == NULL)
		//	ft_destroy();
		
		// int b = 0;
		// while (command_list[b])
		// {
		// 	printf("this,, %s\n", command_list[b]);
		// 	b++;
		// }	
		if (command_list)
		{
			executor(command_list, -1, -1);
			//check_error();
			//end_alles();
		}
	} 
	return (0);
}
