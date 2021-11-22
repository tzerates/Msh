# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tristan <tristan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/15 16:42:21 by ade-la-c          #+#    #+#              #
#    Updated: 2021/11/21 11:49:53 by tristan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= minishell

LIBFT				= ./libft

RDLINE				= /Users/$(USER)/.brew/opt/readline

SRCS				= srcs/main.c				\
					srcs/env.c					\
					srcs/utils/utils.c			\
					srcs/utils/utils1.c			\
					srcs/utils/utils2.c			\
					srcs/utils/utils3.c			\
					srcs/utils/free.c			\
					srcs/utils/env_utils.c		\
					srcs/utils/env_utils2.c		\
					srcs/utils/env_utils3.c		\
					srcs/utils/split_slash.c	\
					srcs/parsing/parsing.c		\
					srcs/parsing/tokenizer.c	\
					srcs/parsing/expansion.c	\
					srcs/parsing/lexing.c		\
					srcs/builtin/cd.c			\
					srcs/builtin/echo.c			\
					srcs/builtin/env.c			\
					srcs/builtin/execpath.c		\
					srcs/builtin/exit.c			\
					srcs/builtin/export.c		\
					srcs/builtin/pwd.c			\
					srcs/builtin/unset.c		\
					srcs/cmd/cmd.c				\
					srcs/cmd/ft_error.c			\
					srcs/cmd/pipe.c				\

OBJS				= $(SRCS:.c=.o)

CC					= gcc

RM					= rm -f

CFLAGS				= -Wall -Werror -Wextra -I. -g -fsanitize=address

INC					= -I ${LIBFT} -I ${RDLINE}/include -I ./inc

LIB					= -L ${LIBFT} -lft -L ${RDLINE}/lib -lreadline

CL_GREY				= \033[38;2;128;128;128m

CL_GREEN			= \033[38;2;0;153;0m

CL_RESET			= \033[0m

.c.o:
					@${CC} ${CFLAGS} -c $^ -o $@

all:			$(NAME)

$(NAME):		$(OBJS)
					@echo "$(CL_GREEN)-> COMPILING LIBFT$(CL_RESET)"
					@echo "$(CL_GREY)"
					$(MAKE) -C $(LIBFT)
					@echo "$(CL_RESET)"
					@echo "$(CL_GREEN)-> COMPILING MINISHELL$(CL_RESET)"
					@echo "$(CL_GREY)"
					${CC} ${CFLAGS} -o $(NAME) $(OBJS) $(LIB)
					@echo "$(CL_RESET)"

clean:
					@echo "$(CL_GREEN)-> CLEAN$(CL_RESET)"
					@echo "$(CL_GREY)"
					@$(MAKE) -C $(LIBFT) clean
					$(RM) $(OBJS)
					@echo "$(CL_RESET)"

fclean:			clean
					@echo "$(CL_GREEN)-> FCLEAN$(CL_RESET)"
					@echo "$(CL_GREY)"
					@$(MAKE) -C $(LIBFT) fclean
					$(RM) $(NAME)
					@echo "$(CL_RESET)"

re:				fclean all

mclean:			all clean

.PHONY:			all clean fclean re mclean
