#include "../inc/minishell.h"

void    init_minishell(char **envp, t_minishell g_minishell)
{
    g_minishell.status_code = 0;
    g_minishell.on_fork = 0;
    g_minishell.envp_list = get_envp_list(envp);
	g_minishell.envp = get_envp();
	g_minishell.builtins[0] = ft_echo;
	g_minishell.builtins[1] = ft_cd;
	g_minishell.builtins[2] = ft_pwd;
	g_minishell.builtins[3] = ft_export;
	g_minishell.builtins[4] = ft_unset;
	g_minishell.builtins[5] = ft_env;
	g_minishell.builtins[6] = ft_exit;
}