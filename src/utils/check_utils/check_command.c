/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/12/12 18:29:36 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_red_output(char *redirect)
{
	if (ft_strcmp(redirect, ">") == 0 || ft_strcmp(redirect, ">>") == 0)
		return (1);
	return (0);
}

int	check_red_input(char *redirect)
{
	if (ft_strcmp(redirect, "<") == 0 || ft_strcmp(redirect, "<<") == 0)
		return (1);
	return (0);
}

int	check_redirect(char *str)
{
	if (ft_strcmp(">", str) == 0 || ft_strcmp(">>", str) == 0 || ft_strcmp("<",
			str) == 0 || ft_strcmp("<<", str) == 0)
		return (1);
	return (0);
}
