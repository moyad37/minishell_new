/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 19:45:54 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_valid_unset(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalpha(var[i]) && !ft_isdigit(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	remove_key_after_check(t_node **envp_list, char *key)
{
	t_node	*curr;
	t_node	*prev;

	curr = *envp_list;
	prev = *envp_list;
	if (ft_strcmp(curr->key, key) == 0)
	{
		*envp_list = (*envp_list)->next;
		ft_lstdelone(curr, &free);
		return ;
	}
	while (ft_strcmp(curr->key, key) != 0 && curr)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	prev->next = curr->next;
	ft_lstdelone(curr, &free);
}

static int	next_step_unset(char *delet_var)
{
	if (!check_valid_unset(delet_var))
	{
		p_fd(2, "bash: unset: `%s': not a valid identifier\n", delet_var);
		return (1);
	}
	if (key_ist_da(g_minishell.envp_list, delet_var))
	{
		remove_key_after_check(&g_minishell.envp_list, delet_var);
		update_env();
	}
	return (0);
}

int	ft_unset(t_command cmd)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (cmd.arg_counter > 1)
	{
		while (cmd.args[i])
		{
			if (next_step_unset(cmd.args[i]))
				status = 1;
			i++;
		}
	}
	if (g_minishell.in_child_process)
		end_pro_child(0, status);
	return (status);
}
