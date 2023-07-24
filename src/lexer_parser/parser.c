#include "../../inc/minishell.h"

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

static char	*extract_key(char *var)
{
	/*
	char	*end_var;
	char	*key;

	end_var = var;
	if (var[0] == '?')
		return (ft_strdup("?"));
	while (is_bash_char(*end_var))
		end_var++;
	key = ft_substr(var, 0, end_var - var);
	return (key);
	*/
	char *end_var = var;
    char *key;
    if (var[0] == '?')
        return ft_strdup("?");
    while (is_bash_char(*end_var))
        end_var++;
    key = ft_substr(var, 0, end_var - var);
    return key;
}