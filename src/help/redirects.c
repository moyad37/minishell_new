#include "../../inc/minishell.h"


static void	filter_and_copy_non_redirects(char **new, char **copy)
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

static int	count_non_redirect_tokens(char **tokens)
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

static void	remove_redirect(char ***command_args)
{
	int		tokens_amount;
	char	**new_tokens;

	tokens_amount = count_non_redirect_tokens(*command_args);
	new_tokens = ft_calloc(sizeof(char *), tokens_amount + 1);
	filter_and_copy_non_redirects(new_tokens, *command_args);
	FreeMatrix((void **)*command_args);
	*command_args = new_tokens;
}


void	deleteRedirects(void)
{
	int	i;
	int	args;

	i = 0;
	args = g_minishell.number_of_cmds;
	while (i < args)
	{
		remove_redirect(&g_minishell.commands[i].args);
		i++;
	}
}


