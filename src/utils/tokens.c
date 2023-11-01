/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/25 12:13:00 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

char	**split_string_in_tokens(char *token, int idx)
{
	int		i;
	char	**subtokens;
	char	quoted;

	i = 0;
	if (*token == '\0')
		return (ft_calloc(idx + 1, sizeof(char *)));
	quoted = 0;
	if (check_zitat(token[i]))
		quoted = token[i++];
	while (token[i] && ((quoted && quoted != token[i]) || !check_zitat(token[i])))
		i++;
	if (quoted && check_zitat(token[i]))
		i++;
	subtokens = split_string_in_tokens(token + i, idx + 1);
	subtokens[idx] = ft_substr(token, 0, i);
	return (subtokens);
}
/*
Diese Funktion fügt die Subtokens wieder zu einem einzigen String zusammen.
*/
char	*join_subtokens(char **subtokens, int x)
{
	char	*expanded_token;
	
	expanded_token = ft_strdup("");
	while (subtokens[x])
	{
		append(&expanded_token, subtokens[x]);
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
Schließlich wird der Speicher für das Array subtokens freigegeben.
*/
void	token_handler(char **token, int i)
{
	char	**subtokens;

	subtokens = split_string_in_tokens(*token, 0);
	while (subtokens[i])
	{
		if (subtokens[i][0] != SINGLE_QUOTE && ft_strchr(subtokens[i], '$'))
			replace_variables(subtokens + i, (0));
		i++;
	}
	free(*token);
	*token = join_subtokens(subtokens, 0);
	if (!ft_strlen(*token))
	{
		free(*token);
		*token = NULL;
	}
	free(subtokens);
}