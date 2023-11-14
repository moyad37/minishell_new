/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/11/14 13:25:22 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"
/*
1.Nimmt einen Zeichenkettenpointer (token), einen Index (idx) und einen Startindex (i) als Parameter
2.Zerlegt die Zeichenkette in Tokens, wobei Anführungszeichen die Tokens begrenzen können
3.Gibt ein Array von Zeichenketten zurück, die die Tokens darstellen
*/
char	**split_string_in_tokens(char *token, int idx, int i)
{
	char	**cmd_teile;
	char	zitat;

	if (*token == '\0')
		return (ft_calloc(idx + 1, sizeof(char *)));
	zitat = 0;
	if (check_zitat(token[i]))
		zitat = token[i++];
	while (token[i] && ((zitat && zitat != token[i]) || !check_zitat(token[i])))
		i++;
	if (zitat && check_zitat(token[i]))
		i++;
	cmd_teile = split_string_in_tokens(token + i, idx + 1, 0);
	cmd_teile[idx] = ft_substr(token, 0, i);
	return (cmd_teile);
}
/*
Diese Funktion fügt die Subtokens wieder zu einem einzigen String zusammen.
*/
char	*join_subtokens(char **cmd_teile, int x)
{
	char	*expanded_token;
	
	expanded_token = ft_strdup("");
	while (cmd_teile[x])
	{
		append(&expanded_token, cmd_teile[x]);
		x++;
	}
	return (expanded_token);
}
/*
Die Funktion token_handler nimmt einen Zeiger auf ein Token token als Parameter entgegen.
Sie ruft die Funktion split_string_in_tokens auf, um das Token in Untertoken aufzuteilen.
Dann durchläuft sie die Untertoken und überprüft, ob das erste Zeichen kein einfaches Anführungszeichen
ist und ob das Untertoken den Zeichen '$' enthält. Wenn dies der Fall ist, ruft sie die Funktion replace_variables auf,
um die Variablen in diesem Untertoken zu erweitern. Am Ende wird das ursprüngliche Token freigegeben und das
erweiterte Token wird an seine Stelle gesetzt. Wenn das erweiterte Token leer ist, wird es auf NULL gesetzt.
Schließlich wird der Speicher für das Array cmd_teile freigegeben.
*/
void	token_handler(char **token, int i)
{
	char	**cmd_teile;

	cmd_teile = split_string_in_tokens(*token, 0, 0);
	while (cmd_teile[i])
	{
		if (cmd_teile[i][0] != SINGLE_QUOTE && ft_strchr(cmd_teile[i], '$'))
			replace_variables(cmd_teile + i, (0));
		i++;
	}
	free(*token);
	*token = join_subtokens(cmd_teile, 0);
	if (!ft_strlen(*token))
	{
		free(*token);
		*token = NULL;
	}
	free(cmd_teile);
}