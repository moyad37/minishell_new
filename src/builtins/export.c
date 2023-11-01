/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 19:45:49 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_valid_export(char *var)
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

static void	valid_export_print(t_command cmd)
{
	// char	*key;
	// char	*value;
	t_node	*tmp;
	int		out;

	out = 1;
	//printf("here noch\n");
	check_output_with_pipe(cmd, &out);
	tmp = g_minishell.envp_list;
	while (tmp)
	{
		// key = tmp->key;
		// value = tmp->value;
		if (tmp->key && tmp->value)
			//p_fd(out, "declare -x %s=\"%s\"\n", key, value);
			p_fd(out, "%s=\"%s\"\n", tmp->key, tmp->value);
		else
			//p_fd(out, "declare -x %s\n", key);
			p_fd(out, "%s\n", tmp->key);
		tmp = tmp->next;
	}
}

static void	add_key_to_envp(char *new_var)
{
	char	**key_and_value;
	char	*key;
	char	*value;
	t_node	*new_node;

	if (!ft_strchr(new_var, '=') && key_ist_da(g_minishell.envp_list, new_var))
	{
		//printf("key existiert schon\n");
		return ;
	}
	if (!ft_strchr(new_var, '=') && !key_ist_da(g_minishell.envp_list, new_var))
	{
		new_node = ft_lstnew(new_var, NULL, NULL);
		ft_lstadd_back(&g_minishell.envp_list, new_node);
		return ;
	}
	key_and_value = split_envp(new_var);
	key = key_and_value[0];
	value = key_and_value[1];
	if (!key_ist_da(g_minishell.envp_list, key))
	{
		new_node = ft_lstnew(key, value, new_var);
		ft_lstadd_back(&g_minishell.envp_list, new_node);
	}
	else
		change_value_from_key(&g_minishell.envp_list, key, value);
	ft_free_matrix((void **)key_and_value);
	update_env();
}

int	ft_export(t_command cmd)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (cmd.arg_counter == 1)
	{
		valid_export_print(cmd);
		return (status);
	}
	while (cmd.args[i])
	{
		if (!check_valid_export(cmd.args[i]))
		{
			p_fd(STDERR_FILENO, \
				"bash: export: `%s': not a valid identifier\n", cmd.args[i]);
			status = 1;
		}
		else
			add_key_to_envp(cmd.args[i]);
		i++;
	}
	if (g_minishell.in_child_process)
		end_pro_child(0, status);
	return (status);
}
