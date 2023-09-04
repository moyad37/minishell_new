#include "../../inc/minishell.h"

static int	erkenne_offenes_zitat(char *token)
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

int finde_Syntaxfehler_Index(char **tokens)
{
    int i = 0;
    int before_pipe;
    while (tokens[i] != NULL)
    {
        if (*tokens[i] == '|' && check_pipe_syntax_error(tokens, i))
        {
            before_pipe = check_pipe_syntax_error(tokens, i);
            if (before_pipe == -2)
                return -1;
            return i;
        }
        else if (is_redirect(tokens[i]) && prüfe_Umleitungs_Syntaxfehler(tokens[i + 1]))
        {
            return i;
        }
        else if (erkenne_offenes_zitat(tokens[i]))
        {
            return i;
        }
        i++;
    }
    return -2;
}

void erweitere_und_ersetze_Umgebungsvariablen(char **token)
{
    int i = 0;
    char **subtokens = extrahiere_Subtokens_aus_Token(*token, 0);
    while (subtokens[i])
    {
        if (subtokens[i][0] != SINGLE_QUOTE && strchr(subtokens[i], '$') != NULL)
            erweitere_Umgebungsvariablen(subtokens + i);
        i++;
    }
    free(*token);
    *token = konkateniere_Subtokens_zu_String(subtokens);
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
    int idx_err = finde_Syntaxfehler_Index(*tokens);
    if (idx_err != -2)
        return zeige_Syntaxfehlermeldung(idx_err, *tokens);
    int size = ft_count_matrix((void **)*tokens);
    while ((*tokens)[i])
    {
        erweitere_und_ersetze_Umgebungsvariablen((*tokens) + i);
        i++;
    }
    if (zaehle_Null_Zeiger(size, *tokens) != 0)
        *tokens = bereinige_String_Array(size, *tokens);
    return 0;
}