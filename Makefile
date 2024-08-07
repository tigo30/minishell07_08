# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 15:42:27 by macampos          #+#    #+#              #
#    Updated: 2024/08/07 23:41:57 by tgrunho-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c src/starting_shell.c src/starting_shell_utils.c src/execute_function.c parsing/parsargs.c parsing/check_redirections.c parsing/parsargs_utils.c parsing/parsargs_utils2.c parsing/pars_helpers.c parsing/builtins/cd.c parsing/builtins/echo.c parsing/builtins/env.c parsing/builtins/pwd.c parsing/builtins/export.c \
		parsing/builtins/unset.c parsing/builtins/echo_utils.c parsing/builtins/builtins_utils.c parsing/builtins/exit.c parsing/utils.c parsing/split.c parsing/signals.c  parsing/redirection.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

$(NAME): $(OBJ)
	$(MAKE) -C ./includes/libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L./includes/libft -lft -lm -lreadline

all: $(NAME)

clean:
	cd includes/libft && make clean
	rm -rf $(OBJ)

fclean: clean
	cd includes/libft && make fclean
	rm -rf $(NAME)

norminette:
	python3 -m c_formatter_42 $(SRC) includes/minishell.h
	python3 -m norminette $(SRC) includes/minishell.h

valgrind: $(NAME)
	valgrind --suppressions=readline.supp --leak-check=full --track-fds=yes --track-origins=yes --show-leak-kinds=all ./${NAME}
#valgrind --suppressions=readline.supp --tool=memcheck --tool=callgrind  --track-fds=yes ./${NAME}

re: fclean all