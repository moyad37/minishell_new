#include "../../inc/minishell.h"

static int	has_unclosed_quote(char *token)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (token[i])
	{
		if (zitat(token[i]) && quote == 0)
			quote = token[i];
		else if (zitat(token[i]) && token[i] == quote)
			quote = 0;
		i++;
	}
	return (quote);
}

int get_syntax_error_idx(char **tokens)
{
    int i = 0;
    int before_pipe;
    while (tokens[i] != NULL)
    {
        if (*tokens[i] == '|' && syntax_error_on_pipe(tokens, i))
        {
            before_pipe = syntax_error_on_pipe(tokens, i);
            if (before_pipe == -2)
                return -1;
            return i;
        }
        else if (is_redirect(tokens[i]) && syntax_error_on_redirect(tokens[i + 1]))
        {
            return i;
        }
        else if (has_unclosed_quote(tokens[i]))
        {
            return i;
        }
        i++;
    }
    return -2;
}

void expand_token(char **token)
{
    int i = 0;
    char **subtokens = get_subtokens(*token, 0);
    while (subtokens[i])
    {
        if (subtokens[i][0] != SINGLE_QUOTE && strchr(subtokens[i], '$') != NULL)
            expand_vars(subtokens + i);
        i++;
    }
    free(*token);
    *token = concat_subtokens(subtokens);
    if (!ft_strlen(*token))
    {
        free(*token);
        *token = NULL;
    }
    free(subtokens);
}



int parser(char ***tokens)
{
    int i = 0;
    int idx_err = get_syntax_error_idx(*tokens);
    if (idx_err != -2)
        return print_invalid_syntax(idx_err, *tokens);
    int size = ft_count_matrix((void **)*tokens);
    while ((*tokens)[i])
    {
        expand_token((*tokens) + i);
        i++;
    }
    if (count_null(size, *tokens) != 0)
        *tokens = remove_null(size, *tokens);
    return 0;
}