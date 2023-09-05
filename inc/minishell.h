

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
void	changeDir(char *new_dir);
//void changeDir(char *new_dir);
int		changeHome(void);
//int changeHome(void);
int		getFileType(char *file);
//int getFileType(char *file);
int		ft_cd(t_command cmd);
//int cdCommand(t_command cmd);

//builtin echo

int		ft_echo(t_command cmd);
//int		valid_dash_n(const char* dash_n);
//void	interpret_special_characters(char* str);
//void	print_args(int size, char** args, int out_fd);

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
void remove_target(t_node **envp_list, const char *key);
//static int remove_env_variable(char *delet_var);
int		ft_unset(t_command cmd);
//static int verify_naming_convention(const char *var);


//init
void    init_minishell(char **envp);

//help die_free_close_child
void	ChildProEnd(int heredoc, int exit_code);
void	ft_free_commands(void);
void	cleanupChild(void);
void	cleanup_command_fds(void);
void	die(void);

//help free
void	ft_free(void *ptr);

//help handles
//static void	manageCommandDescriptors(t_command *prev, t_command *curr, t_command *next);
//static int	executeCommandSequence(t_command *prev, t_command *curr, t_command *next);
int	runPipedCommand(int idx, t_command *curr);

//help redirects
//static void	filter_and_copy_non_redirects(char **new, char **copy);
//static void	remove_redirect(char ***command_args);
void	configure_cmd_fds(void);
//static void	konfiguriere_ausgabeumleitung(t_command *cmd, char *redirect, char *filename);
//static void	konfiguriere_eingabeumleitung(t_command *cmd, char *redirect, char *filename);

//help set_fd
void	deleteRedirects(void);
//static int	count_non_redirect_tokens(char **tokens);
//static void	konfiguriere_befehlsdateideskriptoren(t_command *cmd);

//executor executor_utils
void	initCommands(char **tokens, int idx);
//static void	argsGiveStep(char **tokens, int idx);
void	deleteQu(void);
//void	remove_quotes(void);
void	deleteQuote(void);

//executor executor_utils2
//static char	*retrieveBinWay(t_command *command);
//static void	defineBin(t_command *cmd);
//static char	**giveWayDir(void);
void	initBinWay(void);
//static void	erase_empty_quotes_and_ext_quotes(char **tokens);

//executor executor_utils3
//static int	zahlBefehleCount(char **tokens);
void	lerreUnterTokens(char **subtokens);
//static int	checkQuNull(char *str);
//static void	deleteFremdeZitat(char *str);
//static int	run_single_cmd(t_command cmd);

//executor executor
void	executor(char **tokens);
//static void	initExecutor(char **tokens);
//void	loopForNext(int pid, int *status);

//utils atol_split
long int ft_latoi(const char *nptr);
//static int	count_words(const char *s, char c);
char	**ft_split2(const char *s);

//utils append
void	append(char **s1, char *s2);

//utils builtins_utils
int	finde_Position_builtin(char *str);
void	verwalte_Befehlseingabe(t_command cmd, int *fd);
void	verwalte_Befehlsausgabe(t_command cmd, int *fd);
void	stert_builtin(t_command cmd, int (*builtin)(t_command cmd));
void	update_env(void);

//lexer_parser lexer
char	**lexer(char *cmd);
//static void	passe_Befehlsformatierung_an(char *cmd, int *i);
int	insert_spaces_for_formatting(char *str, int pos);
void	update_characters_between_quotes(char *str, char *set1, char *set2);

//lexer_parser lexer2
int	find_position_in_set(char c, char *set);
char	*init_readable_command(char *cmd);
//static void	init_set(char set[6]);

//lexer_parser lexer3
//static int	count_special_marks(char *cmd);
int	fuege_Leerzeichen_fuer_doppelte_Sonderzeichen_ein(char *str, int pos);
//static void	fix_tokens(char **tokens, char set[6]);
//static int	has_duplicate_special_marks(char *str);
char	*erzeuge_lesefreundlichen_Befehl(char *cmd);

//lexer_parser parser
int parser(char ***tokens);
int get_syntax_error_idx(char **tokens);
void expand_token(char **token);
//static char	*extract_key(char *var);

//lexer_parser parser2
char **bereinige_String_Array(int size, char **tokens);
int zaehle_Null_Zeiger(int size, char **tokens);
int check_pipe_syntax_error(char **tokens, int pos);
char	*konkateniere_Subtokens_zu_String(char **subtokens);
char	*ft_strndup(const char *s, size_t n);
//lexer_parser parser3
int zeige_Syntaxfehlermeldung(int idx_err, char **tokens);
int prüfe_Umleitungs_Syntaxfehler(char *next_token);
void	erweitere_Umgebungsvariablen(char **token);
char	**extrahiere_Subtokens_aus_Token(char *token, int idx);

//lexer_parser start
char	**Start_validiere_und_tokenize_Eingabe(char *cmd);

//matrix utils
void	FreeMatrix(void **matrix);
void	FreeMatrix_size_n(void **matrix, int size);
void	ft_free_list(t_node **head);
int	matrixCounter(void **matrix);
void	ft_free_spatial_matrix(void ***matrix);

//utils give envp
char* ft_strncpy(char* destination, const char* source, size_t num);
char **erstelle_Schlüssel_Wert_Matrix(char *env_variable) ;
t_node *create_envp_list(char **envp);
//static int zähle_gültig_envp(char **envp);
char **create_envp_array();

//utils key_utils
char *hol_envp(t_node *envp_list, char *key);
void andere_envp(t_node **envp_list, char *key, char *new_data);
int key_istda(t_node *envp_list, char *key);

//utils swap_fd
//static void	update_input_fd(t_command *command, int new_fd);
//static void	update_output_fd(t_command *command, int new_fd);
void	update_stream_fd(char *stream, t_command *command, int new_fd);

//utils utils
int	count_args(char **tokens);
void	update_args_count(void);
void	redirect_standard_streams_dups(t_command cmd);
void	print_matrix_to_fd(char **matrix, int fd);

//utils heredoc
//static char	*lese_und_validiere_Eingabe(void);
//static void	sig_handle_heredoc(int signal);
//static int	ft_strcmpl(char *s1, char *s2);
//static void	read_and_process_heredoc(int fd, char *arg);
int	heredoc(t_command *cmd, char *arg);

//signals signal_handler
void handler(int sig);

//check_utils check_arg
int check_arg(int ac, char **av, char **envp);

//check_utils check_main
//int is_quote(char c);
int zitat(char c);
int special_mark(char c);
//int	has_error(t_command *cmd);
int	checkErrorExistiert(t_command *cmd);
//int	is_dir(const char *path);
int	checkIsDirectory(const char *path);

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







# ifdef __linux__
#  define NULLABLE "(nil)"
# else
#  define NULLABLE "0x0"
# endif

# define BUFFER_SIZE 1

# define HEX_LWCASE "0123456789abcdef"
# define HEX_UPCASE "0123456789ABCDEF"
# define DEC_DIGITS "0123456789"





int	ft_printf2(int fd, const char *str, ...);