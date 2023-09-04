#include "../../inc/minishell.h"

char **bereinige_String_Array(int size, char **tokens)
{
    int i = 0;
    int j = 0;
    int null_pos = zaehle_Null_Zeiger(size, tokens);
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

int zaehle_Null_Zeiger(int size, char **tokens)
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

int check_pipe_syntax_error(char **tokens, int pos)
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

char	*konkateniere_Subtokens_zu_String(char **subtokens)
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

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = (char *) malloc(sizeof(char) * n + 1);
	while (*(s + i) && i < n)
	{
		*(dup + i) = *(s + i);
		i++;
	}
	*(dup + i) = '\0';
	return (dup);
}
