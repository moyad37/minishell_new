/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/11/14 12:18:12 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
lesezeichen_in_pos fügt Leerzeichen in einen String str an einer bestimmten
Position pos ein. Hier ist eine Aufschlüsselung dessen, was die Funktion tut
*/
int	lesezeichen_in_pos(char *text, int pos)
{
	int	i;

	i = 0;
	if (pos != 0 && *(text - 1) != ' ')
	{
		ft_memmove(text + 1, text, ft_strlen(text));
		text[0] = ' ';
		i++;
		if (text[2] != ' ')
		{
			ft_memmove(text + 3, text + 2, ft_strlen(text));
			text[2] = ' ';
			i++;
		}
	}
	else if (text[1] != ' ')
	{
		ft_memmove(text + 2, text + 1, ft_strlen(text));
		text[1] = ' ';
		i++;
	}
	return (i);
}

static int	check_doppelte_pipe(char *text)
{
	if (*text != '|' && (check_pipe(*text) && *text == *(text + 1)))
		return (1);
	return (0);
}

static void	format_pipe_leerzeichen(char *command, int *i)
{
	if (check_doppelte_pipe(&command[*i]))
		*i += format_foppelt_pipe_leerzeichen(&command[*i], *i) + 2;
	else if (check_pipe(command[*i]))
		*i += lesezeichen_in_pos(&command[*i], *i) + 1;
}
/*
Die Funktion format_cmd nimmt einen Eingabe-String cmd
entgegen und wandelt ihn in einen lesbareren String um. 
Dabei werden bestimmte Zeichen im String modifiziert,
um die Lesbarkeit zu verbessern. Das Ergebnis ist ein neuer
String, der den modifizierten, lesbareren Befehl repräsentiert.
*/
char	*format_cmd(char *input, int index)
{
	char	zitat_char;
	char	*formatted_input;

	zitat_char = '\0';
	formatted_input = init_for_cmd(input);
	if(!formatted_input)
		return (NULL);
	while (formatted_input[index])
	{
		if (check_zitat(formatted_input[index]) && zitat_char == '\0')
		{
			//printf("es ist zitat = %s\n", formatted_input);
			zitat_char = formatted_input[index];
			index++;
		}
		else if (zitat_char == '\0' && check_pipe(formatted_input[index]))
		{
			//printf("es ist meta_char = %s\n", formatted_input);		
			format_pipe_leerzeichen(formatted_input, &index);
		}
		else if (zitat_char == formatted_input[index])
		{
			zitat_char = '\0';
			index++;
		}
		else
			index++;
	}
	//printf("formatted_input = %s\n", formatted_input);
	return (formatted_input);
}