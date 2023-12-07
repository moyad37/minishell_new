/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/06 21:17:07 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_redirect_syntax_error (char *next_cmd)
{
	if (next_cmd == NULL || check_redirect(next_cmd) \
			|| ft_strcmp(next_cmd, "|") == 0)
	{
		g_minishell.status_code = 2;
		return (1);
	}
	return (0);
}

static int	check_pipe_syntax_error(int pos, char **command)
{
	if (pos == 0)
		return (-2);
	if (command[pos + 1] == NULL)
	{
		return (g_minishell.status_code = 2, 1);
	}
	if (ft_strcmp(command[pos + 1], "|") == 0)
	{
		return(g_minishell.status_code = 2, 1);
	}
	return (0);
}

int	check_command_errors(t_command *cmd)
{
	if (g_minishell.heredoc.heredoc_exited != 0 \
		|| cmd->eingabe == -1 || cmd->ausgabe == -1)
		return (1);
	return (0);
}


static int	check_hat_geoffnete_zitat(char *token)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (token[i])
	{
		if (check_zitat(token[i]) && quote == 0)
			quote = token[i];
		else if (check_zitat(token[i]) && token[i] == quote)
			quote = 0;
		i++;
	}
	return (quote);
}

/*
Die Funktion check_syntax_errors durchläuft die Tokens und überprüft
auf verschiedene Syntaxfehler. Wenn das Token dem Zeichen "|" entspricht
und ein Syntaxfehler auftritt, wird der Rückgabewert von check_pipe_syntax_error überprüft.
Wenn der Wert -2 ist, wird -1 zurückgegeben, um anzuzeigen, dass ein Syntaxfehler am
Anfang der Tokens aufgetreten ist. Andernfalls wird der aktuelle Index i zurückgegeben.
Wenn das Token eine Umleitung ist und ein Syntaxfehler auftritt, wird der aktuelle Index i zurückgegeben.
Wenn das Token ein nicht geschlossenes Anführungszeichen hat, wird der aktuelle Index i zurückgegeben.
Wenn kein Syntaxfehler gefunden wird, wird -2 zurückgegeben.
*/
int	check_syntax_errors(char **tokens, int i)
{
	int	pipe_check_key;
	
	while (tokens[i] != NULL)
	{
		if (*tokens[i] == '|' && check_pipe_syntax_error(i, tokens))
		{
			pipe_check_key = check_pipe_syntax_error(i, tokens);
			if (pipe_check_key == -2)
				return (-1);
			return (i);
		}
		else if (check_redirect(tokens[i])
			&& check_redirect_syntax_error (tokens[i + 1]))
			return (i);
		else if (check_hat_geoffnete_zitat(tokens[i]))
			return (-3);
		i++;
	}
	return (-2);
}