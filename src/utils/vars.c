/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/06 21:25:11 by mmanssou         ###   ########.fr       */
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
	char	*index;
	
	index = var;
	if (var[0] == '?')
		return (ft_strdup("?"));
	while (check_valid_var_character(*index))
		index++;
	return (ft_substr(var, 0, index - var));
}
/*
Diese Funktion verarbeitet ein Token, indem sie darin enthaltene Variablen erweitert.
Sie durchläuft die Zeichen im Eingabetoken, identifiziert Variablen (die mit einem $-Zeichen beginnen),
extrahiert den Variablennamen und ersetzt ihn durch seinen entsprechenden Wert aus einer Liste von Umgebungsvariablen.
0 key
1 value
2 new_token
*/
void	replace_variables(char **token, int i)
{
	char	*new_cmd_arr[3];

	new_cmd_arr[2] = ft_strdup("");
	while ((*token)[i])
	{
		if (check_valid_variable_format(&(*token)[i]))
		{
			new_cmd_arr[0] = isolate_key(&(*token)[i + 1]);
			new_cmd_arr[1] = get_key_value(g_minishell.envp_list, new_cmd_arr[0]);
			if ((*token)[i + 1] == '?')
				append(&new_cmd_arr[2], new_cmd_arr[1]);
			else
				append(&new_cmd_arr[2], ft_strdup(new_cmd_arr[1]));
			i += ft_strlen(new_cmd_arr[0]) + 1;
			free(new_cmd_arr[0]);
		}
		else
			append(&new_cmd_arr[2], ft_strndup(&(*token)[i++], 1));
	}
	free(*token);
	*token = new_cmd_arr[2];
}