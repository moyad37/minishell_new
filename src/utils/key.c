/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/12 18:26:12 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append(char **s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(*s1, s2);
	free(*s1);
	free(s2);
	*s1 = new_str;
}

int	key_ist_da(t_node *envp_list, char *key)
{
	char	*curr_key;
	int		comparison;

	while (envp_list != NULL)
	{
		curr_key = envp_list->key;
		comparison = ft_strcmp(curr_key, key);
		if (comparison == 0)
			return (1);
		envp_list = envp_list->next;
	}
	return (0);
}

void	change_value_from_key(t_node **envp_list, char *key, char *new_data)
{
	t_node	*tmp;

	tmp = *envp_list;
	while (ft_strcmp(tmp->key, key) != 0)
		tmp = tmp->next;
	if (tmp->value)
		free(tmp->value);
	if (tmp->env_line)
		free(tmp->env_line);
	tmp->value = ft_strdup(new_data);
	tmp->env_line = ft_strjoin(tmp->key, "=");
	append(&tmp->env_line, ft_strdup(tmp->value));
}

char	*get_key_value(t_node *envp_list, char *key)
{
	if (key[0] == '?')
		return (ft_itoa(g_minishell.status_code));
	if (!key_ist_da(envp_list, key))
		return ("");
	while (ft_strcmp(envp_list->key, key) != 0)
		envp_list = envp_list->next;
	return (envp_list->value);
}
