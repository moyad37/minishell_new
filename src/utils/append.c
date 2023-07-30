#include "../../inc/minishell.h"

void	append(char **s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(*s1, s2);
	free(*s1);
	free(s2);
	*s1 = new_str;
}