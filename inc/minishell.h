

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
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "../src/libft/libft.h"

# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define DEL_ASCII 127
# define SET1 " \t\v\n\f\r"
# define TMPFILE ".tmpheredoc"
# define READ_END 0
# define WR_END 1
# define NO_SUCH_FILE -1
# define DIR_FILE 0
# define REG_FILE 1

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

//builtin

//builtin cd
void	swap_pwds(char *new_dir);
int		change_home(void);
int		type_of_file(char *file);
int		ft_cd(t_command cmd);

//builtin echo

int		ft_echo(t_command cmd);
int		valid_dash_n(const char* dash_n);
void	interpret_special_characters(char* str);
void	print_args(int size, char** args, int out_fd);

//builtin env
int		ft_env(t_command cmd);

//builtin exit
int		ft_exit(t_command cmd);

//builtin export
//static void print_export(t_command cmd);
//static void	exec_export(char *new_var);
int		ft_export(t_command cmd);

//builtin pwd
int		ft_pwd(t_command cmd);

//builtin unset
void delet_specific_node(t_node **envp_list, const char *key);
//static int exec_unset(char *delet_var);
int		ft_unset(t_command cmd);
int is_valid_identifier(const char *var);


//init
void    init_minishell(char **envp);

//help die_free_close_child
void	die_child(int heredoc, int exit_code);
void	ft_free_commands(void);
void	close_fds_in_child(void);
void	close_fds(void);
void	die(void);

//help free
void	ft_free(void *ptr);

//help handles
//static void	handle_dups(t_command *prev, t_command *curr, t_command *next);
//static int	run_n_cmds(t_command *prev, t_command *curr, t_command *next);
int	handle_exec(int idx, t_command *curr);

//help redirects
//static void	copy_tokens(char **new, char **copy);
//static void	remove_redirect(char ***command_args);
void	init_redirects(void);
//static void	set_output_fd(t_command *cmd, char *redirect, char *filename);
//static void	set_input_fd(t_command *cmd, char *redirect, char *filename);

//help set_fd
void	remove_redirects(void);
//static int	exclude_redirects(char **tokens);
//static void	fill_fds(t_command *cmd);

//executor executor_utils
void	init_commands(char **tokens, int idx);
//static void	fill_args(char **tokens, int idx);
void	remove_filename_quotes(void);
void	remove_quotes(void);

//executor executor_utils2
//static char	*get_bin_path(t_command *command);
//static void	set_bin(t_command *cmd);
//static char	**get_path_dirs(void);
void	init_bin_path(void);
//static void	erase_empty_quotes_and_ext_quotes(char **tokens);

//executor executor_utils3
//static int	count_commands(char **tokens);
void	clear_subtokens(char **subtokens);
//static int	is_empty_quote(char *str);
//static char	*get_bin_path(t_command *command);
//static void	erase_external_quotes(char *str);
//static int	run_single_cmd(t_command cmd);

//executor executor
void	executor(char **tokens);
//static void	init_executor(char **tokens);
//void	loop_wait(int pid, int *status);

//utils atol_split
long int ft_latoi(const char *nptr);
//static int	count_words(const char *s, char c);
char	**ft_split2(const char *s);

//utils append
void	append(char **s1, char *s2);

//utils builtins_utils
int	get_builtin_pos(char *str);
void	handle_input(t_command cmd, int *fd);
void	handle_output(t_command cmd, int *fd);
void	run_builtin(t_command cmd, int (*builtin)(t_command cmd));
void	update_env(void);

//lexer_parser lexer
char	**lexer(char *cmd);
//static void	put_space_if_needed(char *cmd, int *i);
int	put_spaces(char *str, int pos);
void	replace_between(char *str, char *set1, char *set2);

//lexer_parser lexer2
int	get_pos(char c, char *set);
char	*init_human_readable_cmd(char *cmd);
//static void	init_set(char set[6]);

//lexer_parser lexer3
//static int	count_metachars(char *cmd);
int	space_duplicate_metachars(char *str, int pos);
//static void	fix_tokens(char **tokens, char set[6]);
//static int	is_duplicate_meta_char(char *str);
char	*human_readable_cmd(char *cmd);

//lexer_parser parser
int parser(char ***tokens);
int get_syntax_error_idx(char **tokens);
void expand_token(char **token);
//static char	*extract_key(char *var);

//lexer_parser parser2
char **remove_null(int size, char **tokens);
int count_null(int size, char **tokens);
int syntax_error_on_pipe(char **tokens, int pos);
char	*concat_subtokens(char **subtokens);
char	*ft_strndup(const char *s, size_t n);
//lexer_parser parser3
int print_invalid_syntax(int idx_err, char **tokens);
int syntax_error_on_redirect(char *next_token);
void	expand_vars(char **token);
char	**get_subtokens(char *token, int idx);

//lexer_parser start
char	**pipeline_validation(char *cmd);

//matrix utils
void	ft_free_matrix(void **matrix);
void	ft_free_matrix_size_n(void **matrix, int size);
void	ft_free_list(t_node **head);
int	ft_count_matrix(void **matrix);
void	ft_free_spatial_matrix(void ***matrix);

//utils give envp
char* ft_strncpy(char* destination, const char* source, size_t num);
char **get_matrix_with_key_value(char *env_variable) ;
t_node *get_envp_list(char **envp);
//static int amount_of_valid_keys(char **envp);
char **get_envp();

//utils key_utils
char *get_key_value(t_node *envp_list, char *key);
void change_value_from_key(t_node **envp_list, char *key, char *new_data);
int key_exists(t_node *envp_list, char *key);

//utils swap_fd
//static void	swap_fd_input(t_command *command, int new_fd);
//static void	swap_fd_output(t_command *command, int new_fd);
void	swap_stream_fd(char *stream, t_command *command, int new_fd);

//utils utils
int	count_args(char **tokens);
void	update_number_of_args(void);
void	make_dups(t_command cmd);
void	ft_print_matrix_fd(char **matrix, int fd);

//utils heredoc
//static char	*validate_line(void);
//static void	handler_heredoc(int signal);
//static int	ft_strcmpl(char *s1, char *s2);
//static void	get_heredoc_fd(int fd, char *arg);
int	heredoc(t_command *cmd, char *arg);

//signals signal_handler
void handler(int sig);

//check_utils check_arg
int check_arg(int ac, char **av, char **envp);

//check_utils check_main
int is_quote(char c);
int is_meta_char(char c);
int	has_error(t_command *cmd);
int	is_dir(const char *path);

//check_utils check_main2
int is_bash_char(char c);
int is_valid_var(char *str);
int is_output_redirect(char *redirect);
int is_input_redirect(char *redirect);
int is_redirect(char *str);

//error_and_free error
int print_error(const char *str, int fd);
//static void	err_on_input_redirect(char *filename);
//static void	err_on_output_redirect(char *filename);
void	handle_error(t_command *cmd, char *filename);