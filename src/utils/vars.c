/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/25 12:17:17 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

/*
Diese Funktion extrahiert einen Schlüssel aus einem gegebenen String, der normalerweise eine Umgebungsvariable in
einer Shell darstellt. Sie beginnt am Anfang des Eingabestrings und bewegt sich vorwärts, bis sie ein Zeichen erreicht,
das kein gültiges Zeichen für eine Bash-Variable ist.
*/
static char	*isolate_key(char *var)
{
	char	*end_var;
	char	*key;

	end_var = var;
	if (var[0] == '?')
		return (ft_strdup("?"));
	while (check_valid_var_character(*end_var))
		end_var++;
	key = ft_substr(var, 0, end_var - var);
	return (key);
}
/*
Diese Funktion verarbeitet ein Token, indem sie darin enthaltene Variablen erweitert.
Sie durchläuft die Zeichen im Eingabetoken, identifiziert Variablen (die mit einem $-Zeichen beginnen),
extrahiert den Variablennamen und ersetzt ihn durch seinen entsprechenden Wert aus einer Liste von Umgebungsvariablen.
*/
void	replace_variables(char **token, int i)
{
	char	*key;
	char	*value;
	char	*new_token;

	new_token = ft_strdup("");
	while ((*token)[i])
	{
		if (check_valid_variable_format(&(*token)[i]))
		{
			key = isolate_key(&(*token)[i + 1]);
			value = get_key_value(g_minishell.envp_list, key);
			if ((*token)[i + 1] == '?')
				append(&new_token, value);
			else
				append(&new_token, ft_strdup(value));
			i += ft_strlen(key) + 1;
			free(key);
		}
		else
			append(&new_token, ft_strndup(&(*token)[i++], 1));
	}
	free(*token);
	*token = new_token;
}