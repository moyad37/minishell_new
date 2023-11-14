/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/11/13 20:36:54 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	counter(void **var)
{
	int	i;

	i = 0;
	while (var[i])
		i++;
	return (i);
}

void	ft_free_list(t_node **head)
{
	t_node	*current;
	t_node	*next;

	if (!head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		if (current->env_line)
			free(current->env_line);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	free_in_n(void **var, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (var[i])
			free(var[i]);
		i++;
	}
	free(var);
}

void	free_var(void **var)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = counter(var);
	while (i < var_len)
	{
		free(var[i]);
		i++;
	}
	free(var);
}

void	free_douple_var(void ***var)
{
	int	i;
	int	j;
	int	var_len;

	i = 0;
	var_len = counter(*var);
	while (i < var_len)
	{
		j = 0;
		while (var[i][j])
		{
			free(var[i][j]);
			j++;
		}
		free(var[i]);
		i++;
	}
	free(var);
}
