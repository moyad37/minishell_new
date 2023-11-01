.SUFFIXES:
.SUFFIXES: .c .o

SHELL       = /bin/sh

NAME        = minishell

SRCS        = 	minishell.c \
				src/init.c \
				src/builtins/cd.c \
				src/builtins/echo.c \
				src/builtins/env.c \
				src/builtins/exit.c \
				src/builtins/export.c \
				src/builtins/pwd.c \
				src/builtins/unset.c \
				src/envp/creat_envp.c \
				src/envp/list_of_envp.c \
				src/lets_start/umleiten/red_delete.c \
				src/lets_start/umleiten/red_init.c \
				src/lets_start/check_start.c \
				src/lets_start/exec.c \
				src/lets_start/exe_init.c \
				src/lets_start/exe_utils.c \
				src/lets_start/parser.c \
				src/lets_start/lex_init.c \
				src/lets_start/lex_utils.c \
				src/lets_start/lexer.c \
				src/sig_handler/handler.c \
				src/sig_handler/handle_exe.c \
				src/utils/check_utils/check_command.c \
				src/utils/check_utils/check.c \
				src/utils/errors/check_error.c \
				src/utils/errors/error_print.c\
				src/utils/errors/get_error.c \
				src/utils/zitat/rm_ziztat.c \
				src/utils/args_utils.c \
				src/utils/clear_tokens.c \
				src/utils/destroy.c \
				src/utils/dup.c \
				src/utils/endProChild.c \
				src/utils/free.c \
				src/utils/get_matrix.c \
				src/utils/handleBuiltins.c \
				src/utils/heredoc.c \
				src/utils/key.c \
				src/utils/replace.c \
				src/utils/seperat.c \
				src/utils/swaping.c \
				src/utils/tokens.c \
				src/utils/update.c \
				src/utils/vars.c 

OBJS        = ${SRCS:.c=.o}

CC          = cc
RM          = rm -f

LIBFT_FLAGS = -L./src/libft -lft -lreadline

CFLAGS      = -Wall -Wextra -Werror #-g3 -I./inc -I./src/libft

all:    ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJS}
	make -C ./src/libft
	${CC} ${OBJS} ${LIBFT_FLAGS} -o ${NAME}

clean:
	make -C ./src/libft clean
	${RM} ${OBJS}

fclean: clean
	make -C ./src/libft fclean
	${RM} ${NAME}

re:     fclean all

.PHONY : all clean fclean re