/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 19:43:51 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	zähle_nicht_umleitungs_tokens(char **tokens)
{
	int	i;
	int	mem_to_alloc;

	i = 0;
	mem_to_alloc = 0;
	while (tokens[i])
	{
		if (is_redirect(tokens[i]))
			i++;
		else
			mem_to_alloc++;
		i++;
	}
	return (mem_to_alloc);
}

static void	copy_red(char **new, char **copy)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (copy[i])
	{
		if (is_redirect(copy[i]))
			i++;
		else
			new[j++] = ft_strdup(copy[i]);
		i++;
	}
}
/*
Diese Funktion entfernt Umleitungs-Tokens aus der Argumentenliste eines Befehls.
Sie berechnet die Anzahl der zu behaltenden Tokens, erstellt ein neues Array ohne Umleitungen,
gibt das alte Array frei und weist das neue Array den Argumenten des Befehls zu.
*/
static void	losche_red(char ***command_args)
{
	int		tokens_amount;
	char	**new_tokens;

	tokens_amount = zähle_nicht_umleitungs_tokens(*command_args);
	new_tokens = ft_calloc(sizeof(char *), tokens_amount + 1);
	copy_red(new_tokens, *command_args);
	ft_free_matrix((void **)*command_args);
	*command_args = new_tokens;
}

void	losche_umleitung(void)
{
	int	i;
	int	args;

	i = 0;
	args = g_minishell.command_anzahl;
	while (i < args)
	{
		losche_red(&g_minishell.commands[i].args);
		i++;
	}
}
