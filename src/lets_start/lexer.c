/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/14 14:55:19 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fix_tokens(char **tokens, char character_set[6])
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		ersatz_char(tokens[i], character_set, " \t\v\n\f\r", 0);
		i++;
	}
}

/*
Die Funktion `lexer` nimmt einen Eingabe-String entgegen und teilt
ihn in einzelne Tokens auf. Dabei werden bestimmte Zeichenfolgen 
im String durch vordefinierte Werte ersetzt. Das Ergebnis ist ein 
Array von Strings, das die einzelnen Tokens repräsentiert.
*/
char	**lexer(char *cmd, int i)
{
	char	*format_text;
	char	**result_tokens;
	char	character_set[6];

	while (++i < 6)
		character_set[i] = i + 1;
	format_text = format_cmd(cmd, 0);
	if (format_text == NULL)
		return (NULL);
	ersatz_char(format_text, " \t\v\n\f\r", character_set, 0);
	result_tokens = ft_split(format_text, 0);
	if (!result_tokens)
	{
		free(format_text);
		return (NULL);
	}
	fix_tokens(result_tokens, character_set);
	free(format_text);
	return (result_tokens);
}
