
#include "../../inc/minishell.h"

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