#include "../../inc/minishell.h"

int is_bash_char(char c)
{
  if (!ft_isalpha(c) && !ft_isdigit(c) && c != '_')
		return (0);
	return (1);
}

int is_valid_var(char *str)
{
    return (str[0] == '$' && (ft_isalpha(str[1]) || str[1] == '_' || str[1] == '?'));
}

int is_output_redirect(char *redirect)
{
    return (ft_strcmp(redirect, ">") == 0 || ft_strcmp(redirect, ">>") == 0);
}

int is_input_redirect(char *redirect)
{
    return (ft_strcmp(redirect, "<") == 0 || ft_strcmp(redirect, "<<") == 0);
}

int is_redirect(char *str)
{
    return (ft_strcmp(">", str) == 0 || ft_strcmp(">>", str) == 0 || ft_strcmp("<", str) == 0 || ft_strcmp("<<", str) == 0);
}