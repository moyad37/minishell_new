/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_ziztat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/11/13 19:55:21 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"

static void	losche_zitat_nach_handle(char **tokens)
{
	int		i;
	char	**subtokens;

	i = 0;
	while (tokens[i] != NULL)
	{
		subtokens = split_string_in_tokens(tokens[i], 0, 0);
		hanlde_zitat(subtokens);
		free(tokens[i]);
		tokens[i] = join_subtokens(subtokens, 0);
		free(subtokens);
		i++;
	}
}

void	losche_zitat(void)
{
	int	i;
	int	args;

	i = 0;
	args = g_minishell.command_anzahl;
	while (i < args)
	{
		losche_zitat_nach_handle(g_minishell.commands[i].args);
		i++;
	}
}

void	handle_files(int i)
{
	int			count;
	t_command	*cmd;
	char		**subtokens;

	while (i < g_minishell.command_anzahl)
	{
		count = 0;
		cmd = &g_minishell.commands[i];
		while (cmd->args[count])
		{
			if (check_redirect(cmd->args[count]))
			{
				subtokens = split_string_in_tokens(cmd->args[count + 1], 0, 0);
				hanlde_zitat(subtokens);
				free(cmd->args[count + 1]);
				cmd->args[++count] = join_subtokens(subtokens, 0);
				free(subtokens);
			}
			count++;
		}
		i++;
	}
}
