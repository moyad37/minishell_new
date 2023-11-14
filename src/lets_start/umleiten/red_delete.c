/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/11/13 20:47:34 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	zähle_nicht_umleitungs_tokens(char **tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (check_redirect(tokens[i]))
			i++;
		else
			j++;
		i++;
	}
	return (j);
}

static void	copy_red(char **new, char **copy)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (copy[i])
	{
		if (check_redirect(copy[i]))
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
	int		nicht_umleitungs_tokens;
	char	**neue_token;

	nicht_umleitungs_tokens = zähle_nicht_umleitungs_tokens(*command_args);
	neue_token = ft_calloc(sizeof(char *), nicht_umleitungs_tokens + 1);
	copy_red(neue_token, *command_args);
	free_var((void **)*command_args);
	*command_args = neue_token;
}

void	losche_umleitung(int i)
{
	int	command_anzahl;

	command_anzahl = g_minishell.command_anzahl;
	while (i < command_anzahl)
	{
		losche_red(&g_minishell.commands[i].args);
		i++;
	}
}
