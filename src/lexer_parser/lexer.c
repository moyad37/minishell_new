#include "../../inc/minishell.h"


char	**lexer(char *cmd)
{
	/*
	char	*str;
	char	**tokens;

	str = human_readable_cmd(cmd);
	replace_between(str, SET1, set);
	tokens = ft_split(str);
	fix_tokens(tokens, set);
	free(str);
	return (tokens);
	*/
	char	set[6];
	init_set(set);
	char *str = human_readable_cmd(cmd);
    replace_between(str, SET1, set);
    char **tokens = ft_split(str);
    fix_tokens(tokens, set);
    free(str);
    return tokens;

}


static void	put_space_if_needed(char *cmd, int *i)
{ /*
	if (is_duplicate_meta_char(&cmd[*i]))
		*i += space_duplicate_metachars(&cmd[*i], *i) + 2;
	else if (is_meta_char(cmd[*i]))
		*i += put_spaces(&cmd[*i], *i) + 1;
	*/
 if (is_duplicate_meta_char(&cmd[*i]))
    {
        *i += space_duplicate_metachars(&cmd[*i], *i) + 2;
    }
    else if (is_meta_char(cmd[*i]))
    {
        *i += put_spaces(&cmd[*i], *i) + 1;
    }
}

int	put_spaces(char *str, int pos)
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

void	replace_between(char *str, char *set1, char *set2)
{
	/*
	int		i;
	int		corresponding_position;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		if (is_quote(str[i]) && quote == '\0')
			quote = str[i];
		else if (quote != '\0' && ft_strchr(set1, str[i]))
		{
			corresponding_position = get_pos(str[i], set1);
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
        if (is_quote(str[i]) && quote == '\0')
        {
            quote = str[i];
        }
        else if (quote != '\0' && strchr(set1, str[i]) != NULL)
        {
            int corresponding_position = get_pos(str[i], set1);
            str[i] = set2[corresponding_position];
        }
        else if (str[i] == quote)
        {
            quote = '\0';
        }
    }

}