#include "../../inc/minishell.h"

int zeige_Syntaxfehlermeldung(int idx_err, char **tokens)
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

int prüfe_Umleitungs_Syntaxfehler(char *next_token)
{
    if (next_token == NULL || is_redirect(next_token) || ft_strcmp(next_token, "|") == 0)
    {
        g_minishell.status_code = 2;
        return 1;
    }
    return 0;
}

static char	*get_variable_key(char *var)
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


void	erweitere_Umgebungsvariablen(char **token)
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
			key = get_variable_key(&(*token)[i + 1]);
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
            key = get_variable_key(&(*token)[i + 1]);
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

char	**extrahiere_Subtokens_aus_Token(char *token, int idx)
{
	/*
	int		i;
	char	**subtokens;
	char	quoted;

	i = 0;
	if (*token == '\0')
		return (ft_calloc(idx + 1, sizeof(char *)));
	quoted = 0;
	if (zitat(token[i]))
		quoted = token[i++];
	while (token[i] && ((quoted && quoted != token[i]) || !zitat(token[i])))
		i++;
	if (quoted && zitat(token[i]))
		i++;
	subtokens = extrahiere_Subtokens_aus_Token(token + i, idx + 1);
	subtokens[idx] = ft_substr(token, 0, i);
	return (subtokens);
	*/
	int i = 0;
    char **subtokens;
    char quoted = 0;
    if (*token == '\0')
        return ft_calloc(idx + 1, sizeof(char *));
    if (zitat(token[i]))
        quoted = token[i++];
    while (token[i] && ((quoted && quoted != token[i]) || !zitat(token[i])))
        i++;
    if (quoted && zitat(token[i]))
        i++;
    subtokens = extrahiere_Subtokens_aus_Token(token + i, idx + 1);
    subtokens[idx] = ft_substr(token, 0, i);
    return subtokens;
}