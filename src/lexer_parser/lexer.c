#include "../../inc/minishell.h"

static void	first_init(char set[6])
{
/*
	set[0] = 1;
	set[1] = 2;
	set[2] = 3;
	set[3] = 4;
	set[4] = 5;
	set[5] = 6;
*/
    char values[6] = {1, 2, 3, 4, 5, 6};
    memcpy(set, values, sizeof(values));
}

static void	update_tokens_with_set(char **tokens, char set[6])
{
	/*
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		update_characters_between_quotes(tokens[i], set, SET1);
		i++;
	}
	*/
	int i;
	i = 0;
	while(tokens[i] != NULL)
	{
        update_characters_between_quotes(tokens[i], set, SET1);
		i++;
	}
}



int	insert_spaces_for_formatting(char *str, int pos)
{
	/*
	int	i;

	i = 0;
	if (pos != 0 && *(str - 1) != ' ')
	{
		ft_memmove(str + 1, str, ft_strlen(str));
		str[0] = ' ';
		i++;
		if (str[2] != ' ')
		{
			ft_memmove(str + 3, str + 2, ft_strlen(str));
			str[2] = ' ';
			i++;
		}
	}
	else if (str[1] != ' ')
	{
		ft_memmove(str + 2, str + 1, ft_strlen(str));
		str[1] = ' ';
		i++;
	}
	return (i);
	
	*/
 int count = 0;
    if (pos != 0 && *(str - 1) != ' ')
    {
        memmove(str + 1, str, strlen(str) + 1);
        str[0] = ' ';
        count++;
        if (str[2] != ' ')
        {
            memmove(str + 3, str + 2, strlen(str) + 1);
            str[2] = ' ';
            count++;
        }
    }
    else if (str[1] != ' ')
    {
        memmove(str + 2, str + 1, strlen(str) + 1);
        str[1] = ' ';
        count++;
    }
    return count;
}

void	update_characters_between_quotes(char *str, char *set1, char *set2)
{
	/*
	int		i;
	int		corresponding_position;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		if (zitat(str[i]) && quote == '\0')
			quote = str[i];
		else if (quote != '\0' && ft_strchr(set1, str[i]))
		{
			corresponding_position = find_position_in_set(str[i], set1);
			str[i] = set2[corresponding_position];
		}
		else if (str[i] == quote)
			quote = '\0';
		i++;
	}
	*/

	    char quote = '\0';
    for (int i = 0; str[i]; i++)
    {
        if (zitat(str[i]) && quote == '\0')
        {
            quote = str[i];
        }
        else if (quote != '\0' && strchr(set1, str[i]) != NULL)
        {
            int corresponding_position = find_position_in_set(str[i], set1);
            str[i] = set2[corresponding_position];
        }
        else if (str[i] == quote)
        {
            quote = '\0';
        }
    }

}

char	**lexer(char *cmd)
{
	/*
	char	*str;
	char	**tokens;

	str = erzeuge_lesefreundlichen_Befehl(cmd);
	update_characters_between_quotes(str, SET1, set);
	tokens = ft_split(str);
	update_tokens_with_set(tokens, set);
	free(str);
	return (tokens);
	*/
	char	set[6];
	first_init(set);
	char *str = erzeuge_lesefreundlichen_Befehl(cmd);
    update_characters_between_quotes(str, SET1, set);
    char **tokens = ft_split2(str);
    update_tokens_with_set(tokens, set);
    free(str);
    return tokens;

}
