#include "../../inc/minishell.h"

int print_invalid_syntax(int idx_err, char **tokens)
{
    char *err_token;
    if (tokens[idx_err + 1] == NULL)
        err_token = ft_strdup("newline");
    else
        err_token = ft_strdup(tokens[idx_err + 1]);
    printf("bash: syntax error near unexpected token `%s'\n", err_token);
    g_minishell.status_code = 2;
    free(err_token);
    return 1;
}

int syntax_error_on_redirect(char *next_token)
{
    if (next_token == NULL || is_redirect(next_token) || ft_strcmp(next_token, "|") == 0)
    {
        g_minishell.status_code = 2;
        return 1;
    }
    return 0;
}


void	expand_vars(char **token)
{
	/*
	int		i;
	char	*key;
	char	*value;
	char	*new_token;

	i = 0;
	new_token = ft_strdup("");
	while ((*token)[i])
	{
		if (is_valid_var(&(*token)[i]))
		{
			key = extract_key(&(*token)[i + 1]);
			value = get_key_value(g_minishell.envp_list, key);
			if ((*token)[i + 1] == '?')
				append(&new_token, value);
			else
				append(&new_token, ft_strdup(value));
			i += ft_strlen(key) + 1;
			free(key);
		}
		else
			append(&new_token, ft_strndup(&(*token)[i++], 1));
	}
	free(*token);
	*token = new_token;
	*/
	 int i = 0;
    char *key;
    char *value;
    char *new_token = ft_strdup("");
    while ((*token)[i])
    {
        if (is_valid_var(&(*token)[i]))
        {
            key = extract_key(&(*token)[i + 1]);
            value = get_key_value(g_minishell.envp_list, key);
            if ((*token)[i + 1] == '?')
                append(&new_token, value);
            else
                append(&new_token, ft_strdup(value));
            i += ft_strlen(key) + 1;
            free(key);
        }
        else
        {
            append(&new_token, ft_strndup(&(*token)[i++], 1));
        }
    }
    free(*token);
    *token = new_token;
}

char	**get_subtokens(char *token, int idx)
{
	/*
	int		i;
	char	**subtokens;
	char	quoted;

	i = 0;
	if (*token == '\0')
		return (ft_calloc(idx + 1, sizeof(char *)));
	quoted = 0;
	if (is_quote(token[i]))
		quoted = token[i++];
	while (token[i] && ((quoted && quoted != token[i]) || !is_quote(token[i])))
		i++;
	if (quoted && is_quote(token[i]))
		i++;
	subtokens = get_subtokens(token + i, idx + 1);
	subtokens[idx] = ft_substr(token, 0, i);
	return (subtokens);
	*/
	int i = 0;
    char **subtokens;
    char quoted = 0;
    if (*token == '\0')
        return ft_calloc(idx + 1, sizeof(char *));
    if (is_quote(token[i]))
        quoted = token[i++];
    while (token[i] && ((quoted && quoted != token[i]) || !is_quote(token[i])))
        i++;
    if (quoted && is_quote(token[i]))
        i++;
    subtokens = get_subtokens(token + i, idx + 1);
    subtokens[idx] = ft_substr(token, 0, i);
    return subtokens;
}