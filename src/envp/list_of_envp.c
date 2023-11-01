/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_of_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/18 21:41:01 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Die Funktion ev_list_get erstellt eine Liste von Umgebungsvariablen aus dem envp-Array.
Sie durchläuft das envp-Array, extrahiert Schlüssel-Wert-Paare für jede Umgebungsvariable
und fügt sie in einen neuen Knoten ein, der der Liste hinzugefügt wird. Dies wird häufig
in einer Shell-Implementierung verwendet, um Umgebungsvariablen zu verwalten
*/
t_node	*ev_list_get(char **envp)
{
	int		i;
	char	**key_and_value;
	t_node	*envp_list;
	t_node	*new_node;

	i = 0;
	envp_list = NULL;
	while (envp[i] != NULL)
	{
		key_and_value = split_envp(envp[i]);
		//printf("######### %d ########", i);
		new_node = ft_lstnew(key_and_value[0], key_and_value[1], envp[i]);
		ft_free_matrix((void **)key_and_value);
		ft_lstadd_back(&envp_list, new_node);
		i++;
	}
	return (envp_list);
}