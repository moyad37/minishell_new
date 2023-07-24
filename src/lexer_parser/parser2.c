#include "../../inc/minishell.h"

char **remove_null(int size, char **tokens)
{
    int i = 0;
    int j = 0;
    int null_pos = count_null(size, tokens);
    char **new_tokens = ft_calloc(sizeof(char *), size - null_pos + 1);
    while (i < size)
    {
        if (tokens[i])
        {
            new_tokens[j] = ft_strdup(tokens[i]);
            j++;
        }
        i++;
    }
    ft_free_matrix_size_n((void **)tokens, size);
    return new_tokens;
}

int count_null(int size, char **tokens)
{
    int i = 0;
    int count = 0;
    while (i < size)
    {
        if (tokens[i] == NULL)
            count++;
        i++;
    }
    return count;
}

int syntax_error_on_pipe(char **tokens, int pos)
{
    if (pos == 0)
        return -2;
    if (tokens[pos + 1] == NULL || ft_strcmp(tokens[pos + 1], "|") == 0)
    {
        g_minishell.status_code = 2;
        return 1;
    }
    return 0;
}

char	*concat_subtokens(char **subtokens)
{
	/*
	int		i;
	char	*expanded_token;

	i = 0;
	expanded_token = ft_strdup("");
	while (subtokens[i])
	{
		append(&expanded_token, subtokens[i]);
		i++;
	}
	return (expanded_token);
	*/
	 int i = 0;
    char *expanded_token = ft_strdup("");
    while (subtokens[i])
    {
        append(&expanded_token, subtokens[i]);
        i++;
    }
    return expanded_token;
}