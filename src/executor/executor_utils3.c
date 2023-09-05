#include "../../inc/minishell.h"

//remove_filename_quotes
void	deleteQu(void)
{
	int			i;
	int			j;
	t_command	*cmd;
	char		**subtokens;

	i = 0;
	while (i < g_minishell.number_of_cmds)
	{
		j = 0;
		cmd = &g_minishell.commands[i];
		while (cmd->args[j])
		{
			if (is_redirect(cmd->args[j]))
			{
				subtokens = extrahiere_Subtokens_aus_Token(cmd->args[j + 1], 0);
				lerreUnterTokens(subtokens);
				free(cmd->args[j + 1]);
				cmd->args[++j] = konkateniere_Subtokens_zu_String(subtokens);
				free(subtokens);
			}
			j++;
		}
		i++;
	}
}
//is_empty_quote
static int	checkQuNull(char *str)
{
	if(*str == str[1])
		return 1;
	return 0;
}
//erase_external_quotes
static void	deleteFremdeZitat(char *str)
{
	int	last_pos;
	int	str_len;

	str_len = ft_strlen(str);
	ft_memmove(str, str + 1, str_len);
	last_pos = str_len - 2;
	ft_memset(str + last_pos, 0, 1);
}
//clear_subtokens
void	lerreUnterTokens(char **subtokens)
{
	int	i;

	i = 0;
	while (subtokens[i])
	{
		if (zitat(*subtokens[i]) && checkQuNull(subtokens[i]))
			ft_memset(subtokens[i], 0, 2);
		else if (zitat(*subtokens[i]))
			deleteFremdeZitat(subtokens[i]);
		i++;
	}
}

/*
static char	*get_bin_path(t_command *command)
{
	int		i;
	char	*bin;
	char	**path_dirs;

	i = 0;
	path_dirs = get_path_dirs();
	while (path_dirs[i] && command->args[0] && ft_strlen(command->args[0]) > 0)
	{
		bin = ft_strjoin(path_dirs[i], command->args[0]);
		if (!is_dir(bin) && access(bin, F_OK | X_OK) == 0)
		{
			FreeMatrix((void **)path_dirs);
			return (bin);
		}
		else if (access(bin, F_OK) == 0 && access(bin, X_OK) == -1)
		{
			command->error = EACCES;
			ft_free(bin);
			break ;
		}
		ft_free(bin);
		i++;
	}
	FreeMatrix((void **)path_dirs);
	return (NULL);
}
*/



