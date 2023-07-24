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

static void	init_set(char set[6])
{
/*
	set[0] = 1;
	set[1] = 2;
	set[2] = 3;
	set[3] = 4;
	set[4] = 5;
	set[5] = 6;
*/
    char values[6] = {1, 2, 3, 4, 5, 6};
    memcpy(set, values, sizeof(values));
}