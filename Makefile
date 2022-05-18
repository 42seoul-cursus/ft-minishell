# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/12 14:11:43 by jeonghwl          #+#    #+#              #
#    Updated: 2022/05/18 15:50:04 by hkim2            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC 				= gcc
RM				= rm -rf
#-Werror을 하면 not uses가 떠서 잠시 주석처리
CFLAGS 			= -Wall -Wextra -g -fsanitize=address#-Werror
NAME 			= minishell

READLINE_LIB 	= -lreadline -L/usr/local/opt/readline/lib
READLINE_INC	= -I/usr/local/opt/readline/include

LIBFT		= libft.a
LIBFT_DIR	= libft

SRC_DIR 	= srcs
SRC 		= 	srcs/ft_tmp.c \
				srcs/minishell.c \
				srcs/print_terminal.c \
				srcs/signal.c \
				srcs/parser/get_token.c \
				srcs/parser/assign_command.c \
				srcs/parser/assign_output_token.c \
				srcs/parser/env_init_key_value.c \
				srcs/parser/assign_output_command.c \
			 	srcs/parser/output_token_len.c \
				srcs/parser/command_split.c \
				srcs/parser/parse.c \
				srcs/execute/execute.c \
				srcs/execute/execute_builtin.c \
				srcs/execute/execute_util.c \
				srcs/execute/env_util.c \
				srcs/execute/ft_env.c \
				srcs/execute/ft_pwd.c \
				srcs/execute/ft_export.c \
				srcs/execute/ft_export_util.c \
				srcs/execute/ft_unset.c \
				srcs/execute/ft_cd.c \
				srcs/execute/ft_cd_util.c \
				srcs/execute/ft_echo.c \
				srcs/execute/ft_exit.c \
				
OBJ_DIR 	= objs
OBJ 		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all : 		$(NAME)

$(NAME) : 	$(LIBFT) $(OBJ)
			$(CC) $(CFLAGS) -o $@ $(OBJ) $(READLINE_LIB) $(READLINE_INC) \
			$(LIBFT)

$(LIBFT) :
			cd $(LIBFT_DIR); make
			cp $(LIBFT_DIR)/$(LIBFT) ./
			mkdir -p $(OBJ_DIR)/execute
			mkdir -p $(OBJ_DIR)/parser
			mkdir -p $(OBJ_DIR)/redirection
			mkdir -p $(OBJ_DIR)/utils

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			$(CC) $(CFLAGS) -c $< -o $(<:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) \
			$(READLINE_INC)

clean :
			cd $(LIBFT_DIR); make clean
			$(RM) $(OBJ) $(OBJ_DIR)

fclean : 	clean
			cd $(LIBFT_DIR); make fclean
			$(RM) $(NAME) $(LIBFT)

re : 		fclean all

.PHONY :	all clean fclean
