/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 20:42:42 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	type_of_file(char *file)
// {
// 	struct stat	file_status;

// 	if (!file)
// 		return (NO_SUCH_FILE);
// 	file_status.st_mode = 0;
// 	stat(file, &file_status);
// 	if (S_ISREG(file_status.st_mode))
// 		return (REG_FILE);
// 	else if (S_ISDIR(file_status.st_mode))
// 		return (DIR_FILE);
// 	return (NO_SUCH_FILE);
// }

// void	swap_pwds(char *new_dir)
// {
// 	char	*pwd;
// 	t_node	**envp;

// 	envp = &g_minishell.envp_list;
// 	pwd = getcwd(NULL, 0);
// 	if (key_ist_da(*envp, "OLDPWD"))
// 		change_value_from_key(envp, "OLDPWD", pwd);
// 	ft_free(pwd);
// 	chdir(new_dir);
// 	pwd = getcwd(NULL, 0);
// 	if (key_ist_da(*envp, "PWD"))
// 		change_value_from_key(envp, "PWD", pwd);
// 	ft_free(pwd);
// }

// int	change_home(void)
// {
// 	char	*value;

// 	value = get_key_value(g_minishell.envp_list, "HOME");
// 	if (ft_strlen(value))
// 		swap_pwds(value);
// 	else
// 	{
// 		p_fd(STDERR_FILENO, "bash: cd: HOME not set\n");
// 		return (1);
// 	}
// 	return (0);
// }

// static void	print_error(t_command cmd, int filetype)
// {
// 	if (filetype == REG_FILE)
// 		p_fd(STDERR_FILENO, \
// 		"bash: cd: %s: Not a directory\n", cmd.args[1]);
// 	else
// 		p_fd(STDERR_FILENO, \
// 		"bash: cd: %s: No such file or directory\n", cmd.args[1]);
// }

// int	ft_cd(t_command cmd)
// {
// 	int	status;
// 	int	filetype;

// 	status = 1;
// 	if (cmd.arg_counter == 1)
// 		status = change_home();
// 	else if (cmd.arg_counter > 2)
// 		p_fd(STDERR_FILENO, "bash: cd: too many arguments\n");
// 	else
// 	{
// 		filetype = type_of_file(cmd.args[1]);
// 		if (filetype == REG_FILE || filetype == NO_SUCH_FILE)
// 			print_error(cmd, filetype);
// 		else
// 		{
// 			status = 0;
// 			swap_pwds(cmd.args[1]);
// 		}
// 	}
// 	update_env();
// 	if (g_minishell.in_child_process)
// 		end_pro_child(0, status);
// 	return (status);
// }

int	is_regular_file(char *file)
{
	struct stat	file_status;

	if (!file)
		return (NO_SUCH_FILE);
	if (stat(file, &file_status) != 0)
		return (NO_SUCH_FILE);
	return (S_ISREG(file_status.st_mode) ? REG_FILE : DIR_FILE);
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

int	ft_cd(t_command cmd)
{
	char *home;
	//printCommand(cmd);
	if (cmd.arg_counter == 1)
	{
		home = get_key_value(g_minishell.envp_list, "HOME");
		if (strlen(home) > 0)
			return (change_directory(home));
		else
			return (p_fd(STDERR_FILENO, "bash: cd: HOME not set\n"), 1);
	}
	else if (cmd.arg_counter == 2 && access(cmd.args[1], F_OK) == -1)
		return (p_fd(STDERR_FILENO, "bash: cd: %s: No such file or directory\n", cmd.args[1]), 1);
	else if (cmd.arg_counter > 2)
		return (p_fd(STDERR_FILENO, "bash: cd: too many arguments\n"), 1);
	else
	{
		int filetype = is_regular_file(cmd.args[1]);
		if (filetype == REG_FILE)
			return (p_fd(STDERR_FILENO, "bash: cd: %s: Not a directory\n", cmd.args[1]), 1);
		else if (filetype == NO_SUCH_FILE)
			return (1);
		else
			return (change_directory(cmd.args[1]));
	}
}