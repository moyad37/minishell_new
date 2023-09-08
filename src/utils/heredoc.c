#include "../../inc/minishell.h"


static char	*lese_und_validiere_Eingabe(void)
{
	char	*line;

	line = readline("> ");
	if (!line)
		return (NULL);
	append(&line, ft_strdup("\n"));
	erweitere_Umgebungsvariablen(&line);
	return (line);
}

static void	sig_handle_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		ChildProEnd(1, 130);
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

static void	read_and_process_heredoc(int fd, char *arg)
{
	int	size;

	signal(SIGINT, sig_handle_heredoc);
	while (1)
	{
		g_minishell.heredoc.line = lese_und_validiere_Eingabe();
		if (!g_minishell.heredoc.line \
			|| !ft_strcmpl(g_minishell.heredoc.line, arg))
		{
			if (g_minishell.heredoc.line)
				ft_free(g_minishell.heredoc.line);
			else
			{
				ft_printf2(STDERR_FILENO, "bash: warning: here-document "\
						"delimited by end of file (wanted `%s`)\n", arg);
				
				// ft_putstr_fd("bash: warning: here-document delimited by end of file wanted: ", 2);
				// ft_putstr_fd(arg, 2);
				// ft_putstr_fd("\n", 2);
			}
			break ;
		}
		size = ft_strlen(g_minishell.heredoc.line);
		write(fd, g_minishell.heredoc.line, size);
		ft_free(g_minishell.heredoc.line);
	}
	close(fd);
	ChildProEnd(1, 0);
}

int	heredoc(t_command *cmd, char *arg)
{
	int		pid;
	int		status;

	g_minishell.on_fork = 2;
	g_minishell.heredoc.fd = open(TMPFILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
		read_and_process_heredoc(g_minishell.heredoc.fd, arg);
	waitpid(pid, &status, 0);
	g_minishell.on_fork = 0;
	close(g_minishell.heredoc.fd);
	if (status != 0)
		return (1);
	update_stream_fd("input", cmd, open(TMPFILE, O_RDWR));
	return (0);
}
