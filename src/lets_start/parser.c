/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 19:42:36 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
Die Funktion handle_syntax_error_p wird verwendet, um einen Syntaxfehler zu behandeln
und eine Fehlermeldung auszugeben. Sie nimmt den Index des fehlerhaften Tokens und ein Array von Tokens als Parameter.
Die Funktion überprüft, ob das Token nach dem fehlerhaften Token NULL ist. Wenn ja, wird "newline" als
Fehlermeldung verwendet, sonst wird das nächste Token als Fehlermeldung verwendet.
*/
static int	handle_syntax_error_p(int idx_err, char **tokens)
{
	char	*err_token;

	if (tokens[idx_err + 1] == NULL)
		err_token = ft_strdup("newline");
	else
		err_token = ft_strdup(tokens[idx_err + 1]);
	p_fd(2, "bash: syntax error near unexpected token `%s'\n", err_token);
	g_minishell.status_code = 2;
	free(err_token);
	return (1);
}

static int	get_count_invalid_tokens(int size, char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < size)
	{
		if (tokens[i] == NULL)
			count++;
		i++;
	}
	return (count);
}

static char	**filter_null_values(int size, char **tokens)
{
	int		i;
	int		j;
	int		null_pos;
	char	**new_tokens;

	i = 0;
	j = 0;
	null_pos = get_count_invalid_tokens(size, tokens);
	new_tokens = ft_calloc(sizeof(char *), size - null_pos + 1);
	while (i < size)
	{
		if (tokens[i])
		{
			new_tokens[j] = ft_strdup(tokens[i]);
			j++;
		}
		i++;
	}
	ft_free_matrix_size_n((void **)tokens, size);
	return (new_tokens);
}

int	parser(char ***tokens, int i)
{
	int		idx_err;
	int		size;

	idx_err = check_syntax_errors(*tokens, 0);
	if (idx_err != -2)
		return (handle_syntax_error_p(idx_err, *tokens));
	size = ft_count_matrix((void **)*tokens);
	while ((*tokens)[i])
	{
		token_handler((*tokens) + i, (0));
		i++;
	}
	if (get_count_invalid_tokens(size, *tokens) != 0)
		*tokens = filter_null_values(size, *tokens);
	return (0);
}
