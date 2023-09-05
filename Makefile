.SUFFIXES:
.SUFFIXES: .c .o

SHELL       = /bin/sh

NAME        = minishell

SRCS        = minishell.c \
            src/builtin/cd.c src/builtin/echo.c src/builtin/env.c src/builtin/exit.c src/builtin/export.c src/builtin/pwd.c src/builtin/unset.c \
            src/check_utils/check_arg.c src/check_utils/check_main.c src/check_utils/check_main2.c \
            src/errors_and_free/error.c \
            src/executor/executor.c src/executor/executor_utils.c src/executor/executor_utils2.c src/executor/executor_utils3.c \
            src/help/die_free_close_child.c src/help/free.c src/help/handles.c src/help/redirects.c src/help/set_fd.c \
            src/lexer_parser/lexer.c src/lexer_parser/lexer2.c src/lexer_parser/lexer3.c src/lexer_parser/parser.c src/lexer_parser/parser2.c src/lexer_parser/parser3.c src/lexer_parser/start.c \
            src/signals/signal_handler.c \
            src/utils/atol_split.c src/utils/matrix_utils.c src/utils/builtins_utils.c src/utils/give_envp.c src/utils/heredoc.c src/utils/key_utils.c src/utils/swap_fd.c src/utils/utils.c src/utils/append.c \
            src/init.c 

OBJS        = ${SRCS:.c=.o}

CC          = cc
RM          = rm -f

LIBFT_FLAGS = -L./src/libft -lft -lreadline

CFLAGS      = -Wall -Wextra -Werror -g3 -I./inc -I./src/libft

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
