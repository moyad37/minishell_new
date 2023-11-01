/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou  <mmanssou@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/09/13 15:23:59 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstnew(char *key, char *value, char *var)
{
	t_node	*new_node;

	new_node = (malloc(sizeof(t_node)));
	if (!new_node)
		return (0);
	if (key)
		new_node->key = ft_strdup(key);
	else
		new_node->key = NULL;
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	if (var)
		new_node->env_line = ft_strdup(var);
	else
		new_node->env_line = NULL;
	new_node->next = NULL;
	return (new_node);
}
