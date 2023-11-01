/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/10/28 19:46:05 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"


static char	*validate_line(void)
{
	char	*line;

	line = readline("> ");
	if (!line)
		return (NULL);
	append(&line, ft_strdup("\n"));
	replace_variables(&line, 0);
	return (line);
}

static void	handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		end_pro_child(1, 130);
	}
}

static int	ft_strcmpl(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '\n' && s2[i] == '\0')
		return (0);
	return (s1[i] - s2[i]);
}

static void	get_heredoc_fd(int fd, char *arg)
{
	int	size;

	signal(SIGINT, handler_heredoc);
	while (1)
	{
		g_minishell.heredoc.line = validate_line();
		if (!g_minishell.heredoc.line \
			|| !ft_strcmpl(g_minishell.heredoc.line, arg))
		{
			if (g_minishell.heredoc.line)
				ft_free(g_minishell.heredoc.line);
			else
			{
				p_fd(STDERR_FILENO, "bash: warning: here-document "\
						"delimited by end of file (wanted `%s`)\n", arg);
			}
			break ;
		}
		size = ft_strlen(g_minishell.heredoc.line);
		write(fd, g_minishell.heredoc.line, size);
		ft_free(g_minishell.heredoc.line);
	}
	close(fd);
	end_pro_child(1, 0);
}

int	heredoc(t_command *cmd, char *arg)
{
	int		pid;
	int		status;

	g_minishell.in_child_process = 2;
	g_minishell.heredoc.fd = open(TMPFILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
		get_heredoc_fd(g_minishell.heredoc.fd, arg);
	waitpid(pid, &status, 0);
	g_minishell.in_child_process = 0;
	close(g_minishell.heredoc.fd);
	if (status != 0)
		return (1);
	swap_stream_fd("input", cmd, open(TMPFILE, O_RDWR));
	return (0);
}
