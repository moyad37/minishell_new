/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/11/13 20:46:07 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
Die Funktion handle_syntax_error_p wird verwendet, um einen Syntaxfehler zu behandeln
und eine Fehlermeldung auszugeben. Sie nimmt den Index des fehlerhaften Tokens und ein Array von Tokens als Parameter.
Die Funktion überprüft, ob das Token nach dem fehlerhaften Token NULL ist. Wenn ja, wird "newline" als
Fehlermeldung verwendet, sonst wird das nächste Token als Fehlermeldung verwendet.
*/
static int	handle_syntax_error_p(int error_syntax_code, char **tokens)
{
	char	*error_msg;

	if (tokens[error_syntax_code + 1] == NULL)
		error_msg = ft_strdup("newline");
	else
		error_msg = ft_strdup(tokens[error_syntax_code + 1]);
	p_fd(2, "bash: syntax error near unexpected token `%s'\n", error_msg);
	//g_minishell.status_code = 2;
	//free(error_msg);
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
	// int		i;
	// int		j;
	int		invalid_tok_count;
	char	**new_tokens;

	// i = 0;
	// j = 0;
	invalid_tok_count = get_count_invalid_tokens(size, tokens, -1);
	new_tokens = ft_calloc(sizeof(char *), size - invalid_tok_count + 1);
	// while (x < size)
	// {
	// 	if (tokens[x])
	// 	{
	// 		new_tokens[y] = ft_strdup(tokens[x]);
	// 		y++;
	// 	}
	// 	x++;
	// }
		while (x++ < size)
		if (tokens[x])
			new_tokens[y++] = ft_strdup(tokens[x]);
	//free_in_n((void **)tokens, size);
	return (free_in_n((void **)tokens, size), new_tokens);
}

int	parser(char ***tokens, int i)
{
	int		error_syntax_code;
	int		matrex_counter;
	
	error_syntax_code = check_syntax_errors(*tokens, 0);
	if (error_syntax_code != -2)
		return (handle_syntax_error_p(error_syntax_code, *tokens));
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
