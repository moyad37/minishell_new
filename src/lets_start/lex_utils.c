/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/24 13:54:08 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
lesezeichen_in_pos fügt Leerzeichen in einen String str an einer bestimmten
Position pos ein. Hier ist eine Aufschlüsselung dessen, was die Funktion tut
*/
int	lesezeichen_in_pos(char *str, int pos)
{
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
}

static int	check_doppelte_pipe(char *str)
{
	if (*str != '|' && (check_pipe(*str) && *str == *(str + 1)))
		return (1);
	return (0);
}

static void	format_pipe_leerzeichen(char *cmd, int *i)
{
	if (check_doppelte_pipe(&cmd[*i]))
		*i += format_foppelt_pipe_leerzeichen(&cmd[*i], *i) + 2;
	else if (check_pipe(cmd[*i]))
		*i += lesezeichen_in_pos(&cmd[*i], *i) + 1;
}
/*
Die Funktion format_cmd nimmt einen Eingabe-String cmd
entgegen und wandelt ihn in einen lesbareren String um. 
Dabei werden bestimmte Zeichen im String modifiziert,
um die Lesbarkeit zu verbessern. Das Ergebnis ist ein neuer
String, der den modifizierten, lesbareren Befehl repräsentiert.
*/
char	*format_cmd(char *cmd, int i)
{
	char	quoted;
	char	*new_cmd;

	quoted = '\0';
	new_cmd = init_for_cmd(cmd);
	if(!new_cmd)
		return (NULL);
	while (new_cmd[i])
	{
		if (check_zitat(new_cmd[i]) && quoted == '\0')
		{
			//printf("es ist zitat = %s\n", new_cmd);
			quoted = new_cmd[i];
			i++;
		}
		else if (quoted == '\0' && check_pipe(new_cmd[i]))
		{
			//printf("es ist meta_char = %s\n", new_cmd);		
			format_pipe_leerzeichen(new_cmd, &i);
		}
		else if (quoted == new_cmd[i])
		{
			quoted = '\0';
			i++;
		}
		else
			i++;
	}
	//printf("new_cmd = %s\n", new_cmd);
	return (new_cmd);
}