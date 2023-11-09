/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/11/09 15:06:20 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fix_tokens(char **tokens, char character_set[6])
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		ersatz_char(tokens[i], character_set, SET1, 0);
		i++;
	}
}

// static void	init_set(char set[6])
// {
// 	set[0] = 1;
// 	set[1] = 2;
// 	set[2] = 3;
// 	set[3] = 4;
// 	set[4] = 5;
// 	set[5] = 6;
// }
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

	//init_set(character_set);
	while(++i < 6)
		character_set[i] = i + 1;
	// character_set[0] = 1;
	// character_set[1] = 2;
	// character_set[2] = 3;
	// character_set[3] = 4;
	// character_set[4] = 5;
	// character_set[5] = 6;
	format_text = format_cmd(cmd, 0);
	if(format_text == NULL)
		return (NULL);
	ersatz_char(format_text, SET1, character_set, 0);
	result_tokens = ft_split(format_text);
	if(!result_tokens)
	{
		free(format_text);
		return(NULL);
	}
	fix_tokens(result_tokens, character_set);
	free(format_text);
	
	// int i = 0;
	// while (result_tokens[i])
	// {
	// 	printf("result_tokens[%d] = %s\n", i, result_tokens[i]);
	// 	i++;
	// }
	return (result_tokens);
}
