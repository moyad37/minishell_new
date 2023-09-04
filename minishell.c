#include "inc/minishell.h"

t_minishell g_minishell;

int main(int ac, char **av, char **envp)
{
    char    *cmd_line;
    char    **tokens;
    if(!check_arg(ac, av, envp))
        print_error("arg error, make sure you have like so : './minishell' \n", 2);
    signal(SIGINT, handler);
    signal(SIGQUIT, SIG_IGN);
    init_minishell(envp);
    while (1)
    {
        cmd_line = readline("$ ");
        tokens = Start_validiere_und_tokenize_Eingabe(cmd_line);
        if (tokens)
        {
            executor(tokens);
        }
    }
    
}