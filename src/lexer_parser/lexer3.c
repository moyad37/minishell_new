#include "../../inc/minishell.h"

static int	count_metachars(char *cmd)
{
	/*
	
	int		i;
	int		amount_of_metachars;

	i = 0;
	amount_of_metachars = 0;
	while (cmd[i])
	{
		if (is_meta_char(cmd[i]))
			amount_of_metachars++;
		i++;
	}
	return (amount_of_metachars);
	*/
	int amount_of_metachars = 0;
    for (int i = 0; cmd[i]; i++)
    {
        if (is_meta_char(cmd[i]))
        {
            amount_of_metachars++;
        }
    }
    return amount_of_metachars;
}

int	space_duplicate_metachars(char *str, int pos)
{
	/*
	int	i;

	i = 0;
	if (pos != 0 && *(str - 1) != ' ')
	{
		ft_memmove(str + 1, str, ft_strlen(str));
		str[0] = ' ';
		i++;
		if (str[3] != ' ')
		{
			ft_memmove(str + 4, str + 3, ft_strlen(str));
			str[3] = ' ';
			i++;
		}
	}
	else if (str[2] != ' ')
	{
		ft_memmove(str + 3, str + 2, ft_strlen(str));
		str[2] = ' ';
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
        if (str[3] != ' ')
        {
            memmove(str + 4, str + 3, strlen(str) + 1);
            str[3] = ' ';
            count++;
        }
    }
    else if (str[2] != ' ')
    {
        memmove(str + 3, str + 2, strlen(str) + 1);
        str[2] = ' ';
        count++;
    }
    return count;
}

static void	fix_tokens(char **tokens, char set[6])
{
	/*
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		replace_between(tokens[i], set, SET1);
		i++;
	}
	*/
	for (int i = 0; tokens[i] != NULL; i++)
    {
        replace_between(tokens[i], set, SET1);
    }
}

static int	is_duplicate_meta_char(char *str)
{
	/*
	
	if (*str != '|' && (is_meta_char(*str) && *str == *(str + 1)))
		return (1);
	return (0);
	*/
	 return (*str != '|' && (is_meta_char(*str) && *str == *(str + 1)));
}


char	*human_readable_cmd(char *cmd)
{
	/*
	int		i;
	char	quoted;
	char	*new_cmd;

	i = 0;
	quoted = '\0';
	new_cmd = init_human_readable_cmd(cmd);
	while (new_cmd[i])
	{
		if (is_quote(new_cmd[i]) && quoted == '\0')
		{
			quoted = new_cmd[i];
			i++;
		}
		else if (quoted == '\0' && is_meta_char(new_cmd[i]))
			put_space_if_needed(new_cmd, &i);
		else if (quoted == new_cmd[i])
		{
			quoted = '\0';
			i++;
		}
		else
			i++;
	}
	return (new_cmd);
	
	*/

 char quoted = '\0';
    char *new_cmd = init_human_readable_cmd(cmd);
    for (int i = 0; new_cmd[i];)
    {
        if (is_quote(new_cmd[i]) && quoted == '\0')
        {
            quoted = new_cmd[i];
            i++;
        }
        else if (quoted == '\0' && is_meta_char(new_cmd[i]))
        {
            put_space_if_needed(new_cmd, &i);
        }
        else if (quoted == new_cmd[i])
        {
            quoted = '\0';
            i++;
        }
        else
        {
            i++;
        }
    }
    return new_cmd;
}
