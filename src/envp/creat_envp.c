/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/07 19:46:32 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Die Funktion count_keys_valid dient dazu, die Anzahl der gültigen
Schlüssel-Wert-Paare in einer verketteten Liste von Umgebungsvariablen
zu ermitteln. Hier ist eine kurze Erklärung des Codes
*/
static int	count_keys_valid(t_node **envp)
{
	int		size;
	t_node	*tmp;

	size = 0;
	tmp = *envp;
	while (tmp)
	{
		if (tmp->value && tmp->env_line)
			size++;
		tmp = tmp->next;
	}
	return (size);
}

/*
Die Funktion creat_valid_envp erstellt ein char **-Array,
das gültige Umgebungsvariablen in einem bestimmten Format
speichert. Sie verwendet die Umgebungsvariablen aus der
globalen Shell-Struktur, extrahiert gültige Schlüssel-Wert-Paare
und speichert sie in diesem Array. Das Format ist für die Verwendung
in Unix-ähnlichen Betriebssystemen geeignet.
*/
char	**creat_valid_envp(void)
{
	int		i;
	int		size;
	char	**envp;
	t_node	*tmp;

	i = 0;
	tmp = g_minishell.envp_list;
	size = count_keys_valid(&g_minishell.envp_list);
	envp = ft_calloc(sizeof(char *), size + 1);
	while (tmp)
	{
		if (tmp->value && tmp->env_line)
		{
			envp[i] = ft_strdup(tmp->env_line);
			i++;
		}
		tmp = tmp->next;
	}
	return (envp);
}
