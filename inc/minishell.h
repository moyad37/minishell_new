

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <readline/readline.h>
# include <dirent.h>
# include <fcntl.h>
# include <string.h>
# include "errors.h"
# include "../src/libft/libft.h"
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>

# define ERRORS_H

# define ENOENT 2
# define EACCES 13
# define ENAMETOOLONG 36
# define EISDIR 126
# define ENOCMD 127

typedef struct s_command
{
	int		pipe[2];
	int		number_of_args;
	int		input_fd;
	int		output_fd;
	int		error;
	char	*bin_path;
	char	**args;
}	t_command;

typedef struct s_heredoc
{
	int			fd;
	int			heredoc_exited;
	char		*line;
}	t_heredoc;

typedef struct s_minishell
{
	int			status_code;
	int			number_of_cmds;
	char		**envp;
	int			on_fork;
	int			(*builtins[7])(t_command cmd);
	t_heredoc	heredoc;
	t_node		*envp_list;
	t_command	*commands;
}	t_minishell;

extern t_minishell	g_minishell;

//init
void    init_minishell(char **envp, t_minishell g_minishell);

//matrix utils
void	ft_free_matrix(void **matrix);
void	ft_free_matrix_size_n(void **matrix, int size);
void	ft_free_list(t_node **head);
int	ft_count_matrix(void **matrix);
void	ft_free_spatial_matrix(void ***matrix);

//give envp
char* ft_strncpy(char* destination, const char* source, size_t num);
char **get_matrix_with_key_value(char *env_variable) ;
char **get_envp_list(char **envp);
int amount_of_valid_keys(char **envp);
char **get_envp();

//signal_handker
int handler(int sig);

//check_utils check_arg
int check_arg(int ac, char **av, char **envp);

//error
int print_error(const char *str, int fd);