#include "../../inc/minishell.h"

char	**Start_validiere_und_tokenize_Eingabe(char *cmd)
{
	/*
	char	**tokens;

	tokens = NULL;
	if (cmd == NULL)
		die();
	if (cmd[0] == '\0')
		ft_free(cmd);
	else
	{
		add_history(cmd);
		tokens = lexer(cmd);
		ft_free(cmd);
		if (parser(&tokens) == 1 || *tokens == NULL)
		{
			ft_free_matrix((void **)tokens);
			return (NULL);
		}
	}
	return (tokens);
	*/

 if (cmd == NULL)
    {
        die();
        return NULL;
    }

    if (cmd[0] == '\0')
    {
        ft_free(cmd);
        return NULL;
    }

    add_history(cmd);
    char **tokens = lexer(cmd);
    ft_free(cmd);

    if (parser(&tokens) == 1 || *tokens == NULL)
    {
        ft_free_matrix((void **)tokens);
        return NULL;
    }

    return tokens;
}