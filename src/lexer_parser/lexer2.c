#include "../../inc/minishell.h"


int	get_pos(char c, char *set)
{
	/*
	int	i;

	i = 0;
	while (c != set[i])
		i++;
	return (i);
	*/

	    for (int i = 0; set[i]; i++)
    {
        if (c == set[i])
        {
            return i;
        }
    }
    return -1;
}

static int	count_metachars(char *cmd)
{
	/*
	
	int		i;
	int		amount_of_metachars;

	i = 0;
	amount_of_metachars = 0;
	while (cmd[i])
	{
		if (is_meta_char(cmd[i]))
			amount_of_metachars++;
		i++;
	}
	return (amount_of_metachars);
	*/
	int amount_of_metachars = 0;
    for (int i = 0; cmd[i]; i++)
    {
        if (is_meta_char(cmd[i]))
        {
            amount_of_metachars++;
        }
    }
    return amount_of_metachars;
}


char	*init_human_readable_cmd(char *cmd)
{
	/*
	char	*new_cmd;
	int		mem_to_alloc;
	int		max_spaces_to_insert;

	max_spaces_to_insert = count_metachars(cmd) * 2;
	mem_to_alloc = max_spaces_to_insert + ft_strlen(cmd) + 2;
	new_cmd = malloc(sizeof(char) * mem_to_alloc);
	ft_bzero(new_cmd, mem_to_alloc);
	ft_strlcpy(new_cmd, cmd, mem_to_alloc);
	return (new_cmd);
	
	*/
int max_spaces_to_insert = count_metachars(cmd) * 2;
    int mem_to_alloc = max_spaces_to_insert + strlen(cmd) + 2;
    char *new_cmd = malloc(sizeof(char) * mem_to_alloc);
    memset(new_cmd, 0, mem_to_alloc);
    strncpy(new_cmd, cmd, mem_to_alloc);
    return new_cmd;
}

