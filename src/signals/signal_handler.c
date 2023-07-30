
#include "../../inc/minishell.h"

void handler(int sig)
{
    if(!sig)
        print_error("no signal resived. \n", 2);
    if(sig == SIGINT)
        write(STDOUT_FILENO, "\n", 1);
}