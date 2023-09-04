#include "../../inc/minishell.h"

static int	has_duplicate_special_marks(char *str)
{
	/*
	
	if (*str != '|' && (special_mark(*str) && *str == *(str + 1)))
		return (1);
	return (0);
	*/
	 return (*str != '|' && (special_mark(*str) && *str == *(str + 1)));
}

static void	passe_Befehlsformatierung_an(char *cmd, int *i)
{ /*
	if (has_duplicate_special_marks(&cmd[*i]))
		*i += fuege_Leerzeichen_fuer_doppelte_Sonderzeichen_ein(&cmd[*i], *i) + 2;
	else if (special_mark(cmd[*i]))
		*i += insert_spaces_for_formatting(&cmd[*i], *i) + 1;
	*/
 if (has_duplicate_special_marks(&cmd[*i]))
    {
        *i += fuege_Leerzeichen_fuer_doppelte_Sonderzeichen_ein(&cmd[*i], *i) + 2;
    }
    else if (special_mark(cmd[*i]))
    {
        *i += insert_spaces_for_formatting(&cmd[*i], *i) + 1;
    }
}




int	fuege_Leerzeichen_fuer_doppelte_Sonderzeichen_ein(char *str, int pos)
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





char	*erzeuge_lesefreundlichen_Befehl(char *cmd)
{
	/*
	int		i;
	char	quoted;
	char	*new_cmd;

	i = 0;
	quoted = '\0';
	new_cmd = init_readable_command(cmd);
	while (new_cmd[i])
	{
		if (zitat(new_cmd[i]) && quoted == '\0')
		{
			quoted = new_cmd[i];
			i++;
		}
		else if (quoted == '\0' && special_mark(new_cmd[i]))
			passe_Befehlsformatierung_an(new_cmd, &i);
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
    char *new_cmd = init_readable_command(cmd);
    for (int i = 0; new_cmd[i];)
    {
        if (zitat(new_cmd[i]) && quoted == '\0')
        {
            quoted = new_cmd[i];
            i++;
        }
        else if (quoted == '\0' && special_mark(new_cmd[i]))
        {
            passe_Befehlsformatierung_an(new_cmd, &i);
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
