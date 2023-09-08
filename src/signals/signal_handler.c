
#include "../../inc/minishell.h"

//OHNE FEHLER
// void handler(int sig)
// {
//     if(!sig)
//         print_error("no signal resived. \n", 2);
//     if(sig == SIGINT)
//         write(STDOUT_FILENO, "\n", 1);
// }

void	handler(int signal)
{
	if (signal == SIGINT && !g_minishell.on_fork)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGINT && g_minishell.on_fork == 1)
		write(STDOUT_FILENO, "\n", 1);
}