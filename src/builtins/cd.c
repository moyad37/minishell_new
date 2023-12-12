/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/12 17:56:41 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_regular_file(char *file)
{
	struct stat	file_status;

	if (!file)
		return (NO_SUCH_FILE);
	if (stat(file, &file_status) != 0)
		return (NO_SUCH_FILE);
	if (S_ISREG(file_status.st_mode))
		return (REG_FILE);
	else
		return (DIR_FILE);
}

void	update_pwd_env(void)
{
	char	*pwd;
	t_node	**envp;

	pwd = getcwd(NULL, 0);
	envp = &g_minishell.envp_list;
	if (key_ist_da(*envp, "OLDPWD"))
		change_value_from_key(envp, "OLDPWD", pwd);
	free(pwd);
}

int	change_directory(char *new_dir)
{
	if (chdir(new_dir) != 0)
	{
		p_fd(STDERR_FILENO, "bash: cd: %s: No such file or directory\n",
			new_dir);
		return (1);
	}
	update_pwd_env();
	return (0);
}

int	cd_weiter(t_command cmd)
{
	int	filetype;

	filetype = is_regular_file(cmd.args[1]);
	if (filetype == REG_FILE)
		return (p_fd(STDERR_FILENO, "bash: cd: %s: Not a directory\n",
				cmd.args[1]), 1);
	else if (filetype == NO_SUCH_FILE)
		return (1);
	else
		return (change_directory(cmd.args[1]));
	return (0);
}

int	ft_cd(t_command cmd)
{
	char	*home;

	if (cmd.arg_counter == 1 || (cmd.arg_counter == 2 && *cmd.args[1] == '~'))
	{
		home = get_key_value(g_minishell.envp_list, "HOME");
		if (ft_strlen(home) > 0)
			return (change_directory(home));
		else
			return (p_fd(STDERR_FILENO, "bash: cd: HOME not set\n"), 1);
	}
	else if (cmd.arg_counter == 2 && access(cmd.args[1], F_OK) == -1)
		return (p_fd(STDERR_FILENO, "bash: cd: %s: No such file or directory\n",
				cmd.args[1]), 1);
	else if (cmd.arg_counter > 2)
		return (p_fd(STDERR_FILENO, "bash: cd: too many arguments\n"), 1);
	else
	{
		return (cd_weiter(cmd));
	}
	return (0);
}
