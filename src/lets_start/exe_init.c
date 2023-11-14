/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/11/14 13:41:33 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"
/*
1.Nimmt ein Array von Zeichenketten (tokens), den Index des aktuellen Befehls (idx) und einen Startindex (i) als Parameter.
2.Füllt die Argumente für den Befehl im globalen g_minishell-Array basierend auf den übergebenen Tokens. Hierbei wird davon
ausgegangen, dass g_minishell.commands ein Array von Befehlsstrukturen ist.
3.Die Anzahl der Argumente wird aus der globalen Variable g_minishell.commands[idx].arg_counter abgeleitet.
*/
static void	fill_args(char **tokens, int idx, int i)
{
	int	args;

	args = g_minishell.commands[idx].arg_counter;
	while (i < args)
	{
		g_minishell.commands[idx].args[i] = ft_strdup(tokens[i]);
		i++;
	}
}
/*
1.Nimmt ein Array von Zeichenketten (tokens), einen Startindex (x) und einen Zählwert (y) als Parameter.
2.Zählt die Anzahl der Befehle im übergebenen Array, indem es nach dem Trennsymbol "|" sucht.
3.Gibt die Gesamtanzahl der Befehle zurück.
*/
static int	cmd_count(char **tokens, int x, int y)
{
	while (tokens[x])
	{
		if (ft_strcmp("|", tokens[x]) == 0)
			y++;
		x++;
	}
	return (y + 1);
}
/*
Diese Funktion initialisiert die Befehle in einer Shell-Struktur. Sie zählt die Anzahl der Befehle,
initialisiert die entsprechenden Datenstrukturen und ruft fill_args auf, um die Argumente für jeden Befehl vorzubereiten.
1.Nimmt ein Array von Zeichenketten (tokens) und den Index eines Befehls (idx) als Parameter.
2.Initialisiert die Befehlsstruktur im globalen g_minishell-Array.
3.Bestimmt die Gesamtanzahl der Befehle (command_anzahl) und alloziert Speicher für die entsprechenden Datenstrukturen,
wenn idx gleich 0 ist (was darauf hindeutet, dass es sich um den ersten Aufruf handelt).
4.Rekursiv ruft sich selbst auf, um die Befehlsstruktur für jeden Teil der Eingabe zu erstellen.
5.Zählt die Anzahl der Argumente für jeden Befehl und füllt die Argumente mithilfe von fill_args.
*/
void	split_save_cmd_struct(char **tokens, int idx)
{
	int		i;
	int		argument_count;
	int		command_anzahl;

	i = 0;
	if (idx == 0)
	{
		g_minishell.command_anzahl = cmd_count(tokens, 0 ,0);
		command_anzahl = g_minishell.command_anzahl;
		g_minishell.commands = ft_calloc(sizeof(t_command), command_anzahl + 1);
	}
	if (tokens[i] == NULL)
		return ;
	while (tokens[i] && ft_strcmp("|", tokens[i]) != 0)
		i++;
	if (tokens[i] && ft_strcmp("|", tokens[i]) == 0)
		i++;
	split_save_cmd_struct(tokens + i, idx + 1);
	argument_count = count_args(tokens);
	g_minishell.commands[idx].arg_counter = argument_count;
	g_minishell.commands[idx].args = ft_calloc(sizeof(char *), argument_count + 1);
	fill_args(tokens, idx, 0);
}

