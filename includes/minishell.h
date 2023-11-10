/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/11/10 13:52:55 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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

# include <term.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <curses.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "../src/libft/libft.h"

typedef struct s_heredoc
{
	int			fd;
	int			heredoc_exited;
	char		*line;
}	t_heredoc;

typedef struct s_command
{
	int		pipe[2];
	int		arg_counter;
	int		eingabe;
	int		ausgabe;
	int		error;
	char	*executable_path;
	char	**args;
}	t_command;

typedef struct s_minishell
{
	int			shell_lvl;
	int			status_code;
	int			command_anzahl;
	char		**envp;
	int			in_child_process;
	int			(*builtins[7])(t_command cmd);
	t_heredoc	heredoc;
	t_node		*envp_list;
	t_command	*commands;
}	t_minishell;

extern t_minishell	g_minishell;

char	*get_key_value(t_node *envp_list, char *key);
void	change_value_from_key(t_node **envp_list, char *key, char *new_data);
int		key_ist_da(t_node *envp_list, char *key);

t_node	*ev_list_get(char **envp);
char	**split_envp(char *env_variable);
char	**creat_valid_envp(void);

// Builtins
void	execute_builtin_command(t_command cmd, int (*builtin)(t_command cmd));
int		get_befehl(char *str);
int		ft_pwd(t_command cmd);
int		ft_echo(t_command cmd);
int		ft_cd(t_command cmd);
int		ft_export(t_command cmd);
int		ft_unset(t_command cmd);
int		ft_env(t_command cmd);
int		ft_exit(t_command cmd);
//void	check_input_with_pipe(t_command cmd, int *fd);
void	check_output_with_pipe(t_command cmd, int *fd);

// Lexer
char	**lexer(char *cmd, int i);
int		lesezeichen_in_pos(char *str, int pos);
int		format_foppelt_pipe_leerzeichen(char *text, int position);
char	*format_cmd(char *cmd, int i);
void	ersatz_char(char *str, char *set1, char *set2, int i);
char	*init_for_cmd(char *cmd);

// Parser
int		parser(char ***tokens, int i);
int		check_syntax_errors(char **tokens, int i);
void	token_handler(char **token, int i);
char	**split_string_in_tokens(char *token, int idx, int i);
char	*join_subtokens(char **subtokens, int x);
void	replace_variables(char **token, int i);

// Executor
void	executor(char **tokens, int i, int status);
void	init_redirects(void);
void	split_save_cmd_struct(char **tokens, int idx);
void	losche_umleitung(void);
void	losche_zitat(void);
void	get_pfad(int i);
void	update_args_count(int i);
int		handel_get_bid_exe(int idx, t_command *curr);
int		heredoc(t_command *cmd, char *arg);
void	hanlde_zitat(char **subtokens);

// Redirect
int		check_command_errors(t_command *cmd);
void	handle_error(t_command *cmd, char *filename);

// Utils
int		check_zitat(char c);
int		check_pipe(char c);
int		is_bash_word(char *str);
int		check_valid_var_character(char c);
int		check_redirect(char *str);
int		check_red_input(char *redirect);
int		check_red_output(char *redirect);
int		check_directory(const char *path);
void	append(char **s1, char *s2);
int		check_valid_variable_format(char *str);
void	swap_stream_fd(char *stream, t_command *command, int new_fd);
void	close_fds(void);
void	child_fd_close(void);
void	handl_sig(int signal);
void	end_alles(void);
void	ft_free(void *ptr);
void	end_pro_child(int heredoc, int status_code);
int		test_filename(char *filename, char *redirect);
void	update_env(void);
int		count_args(char **tokens);
void	make_dups(t_command cmd);
void	print_error(t_command cmd);

void	ft_print_matrix_fd(char **matrix, int fd);

//init
int	init(char **envp);

//lets_start
char	**check_commands(char *cmd);

//utils/ft_destroy
void	ft_destroy(void);
//utils
char	**seperatByC(const char *str, char c);

//utils/zitat/rm_ziztat
void	handle_files(int i);
int	get_redirect(int i);





void printCommand(t_command cmd);


void	wait_sig(void);

#endif
