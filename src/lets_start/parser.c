/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/07 19:46:09 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
Die Funktion handle_syntax_error_p wird verwendet, um einen Syntaxfehler zu behandeln
und eine Fehlermeldung auszugeben. Sie nimmt den Index des fehlerhaften Tokens und ein Array von Tokens als Parameter.
Die Funktion überprüft, ob das Token nach dem fehlerhaften Token NULL ist. Wenn ja, wird "newline" als
Fehlermeldung verwendet, sonst wird das nächste Token als Fehlermeldung verwendet.
*/
static int	handle_syntax_error_p(int error_syntax_code, char **tokens, int key)
{
	char	*error_msg;
	if(key == 1)
	{
		return (g_minishell.status_code = 2, 1);
	}
	if (tokens[error_syntax_code + 1] == NULL)
		error_msg = ft_strdup("newline");
	else
		error_msg = ft_strdup(tokens[error_syntax_code + 1]);
	p_fd(2, "bash: syntax error near unexpected token `%s'\n", error_msg);
	return (g_minishell.status_code = 2, free(error_msg), 1);
}

static int	get_count_invalid_tokens(int size, char **tokens, int i)
{
	int	count;

	count = 0;
	while (++i < size)
	{
		if (tokens[i] == NULL)
			count++;
	}
	return (count);
}

static char	**filter_null_values(int size, char **tokens, int x, int y)
{
	int		invalid_tok_count;
	char	**new_tokens;

	invalid_tok_count = get_count_invalid_tokens(size, tokens, -1);
	new_tokens = ft_calloc(sizeof(char *), size - invalid_tok_count + 1);
	while (x++ < size)
		if (tokens[x])
			new_tokens[y++] = ft_strdup(tokens[x]);
	return (free_in_n((void **)tokens, size), new_tokens);
}
/*
1.Nimmt ein Array von Zeichenkettenpointern (tokens) und einen Index (i) als Parameter.
2.Überprüft auf Syntaxfehler und behandelt diese.
3.Verarbeitet jeden Token durch den token_handler.
4.Filtert ungültige Tokens und gibt 0 zurück, wenn der Parser erfolgreich ist
*/
int	parser(char ***tokens, int i)
{
	int		error_syntax_code;
	int		matrex_counter;
	
	error_syntax_code = check_syntax_errors(*tokens, 0);
	if (error_syntax_code == -3)
		return (handle_syntax_error_p(error_syntax_code, *tokens, 1));
	if (error_syntax_code != -2)
		return (handle_syntax_error_p(error_syntax_code, *tokens, 0));
	matrex_counter = counter((void **)*tokens);
	while ((*tokens)[i])
	{
		token_handler((*tokens) + i, (0));
		i++;
	}
	if (get_count_invalid_tokens(matrex_counter, *tokens, -1) != 0)
		*tokens = filter_null_values(matrex_counter, *tokens, 0,0 );
	return (0);
}
