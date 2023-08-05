NAME	= minishell
LIBFT_PATH =	./src/libft
SRCS	= minishell.c\
			src/builtin/cd.c src/builtin/echo.c src/builtin/env.c src/builtin/exit.c src/builtin/export.c src/builtin/pwd.c src/builtin/unset.c\
			src/check_utils/check_arg.c src/check_utils/check_main.c src/check_utils/check_main2.c\
			src/errors_and_free/error.c\
			src/executor/executor.c src/executor/executor_utils.c src/executor/executor_utils2.c src/executor/executor_utils3.c\
			src/help/die_free_close_child.c src/help/free.c src/help/hanldes.c src/help/redirects.c src/help/set_fd.c\
			src/lexer_parser/lexer.c src/lexer_parser/lexer2.c src/lexer_parser/lexer3.c src/lexer_parser/parser.c src/lexer_parser/parser2.c src/lexer_parser/parser3.c src/lexer_parser/start.c\
			src/signals/signal_handler.c\
			src/utils/atol_split.c src/utils/builtins_utils.c src/utils/give_envp.c src/utils/heredoc.c src/utils/key_utils.c src/utils/swap_fd.c src/utils/utils.c src/utils/append.c\
			src/init.c src/matrix_utils.c
			
CC		= @clang
LIBS	= -libft -lft -lreadline
CFLAGS	= -Wall -Werror -Wextra
OBJS	= ${SRCS:.c=.o}
LIBFT_FLAGS =	-L $(LIBFT_PATH) -lft

all: libft ${NAME}

libft:
	@make -C $(LIBFT_PATH) --no-print-directory

#.c.o :
#	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS} $(LIBFT_PATH)/libft.a
	@make -s -C libft 
	cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_FLAGS) -lreadline

$(LIBFT_PATH)/libft.a:
	make -C $(LIBFT_PATH) --no-print-directory

clean:
	@rm -f ${OBJS}
	make -C $(LIBFT_PATH) clean --no-print-directory

fclean : clean
	@rm -f ${NAME}
	make -C $(LIBFT_PATH) fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re