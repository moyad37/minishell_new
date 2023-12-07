/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/06 21:53:11 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_valid_var_character(char c)
{
	if (!ft_isalpha(c) && !ft_isdigit(c) && c != '_')
		return (0);
	return (1);
}

int	check_pipe(char c)
{
	if (ft_strchr(">|<", c))
		return (1);
	return (0);
}

int	check_directory(const char *path)
{
	struct stat	file_stat;

	if (!path)
		return (0);
	file_stat.st_mode = 0;
	stat(path, &file_stat);
	return (S_ISDIR(file_stat.st_mode));
}

// singal zitat = 39
// double zitat = 34
int	check_zitat(char c)
{
	if (c == 39 || c == 34)
		return (1);
	return (0);
}

int	check_valid_variable_format(char *str)
{
	if (str[0] == '$' && (ft_isalpha(str[1]) || str[1] == '_' || str[1] == '?'))
		return (1);
	return (0);
}

