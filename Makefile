# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeonghwl <jeonghwl@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/12 14:11:43 by jeonghwl          #+#    #+#              #
#    Updated: 2022/05/12 14:11:49 by jeonghwl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC 				= gcc
RM				= rm -rf
CFLAGS 			= -Wall -Wextra -Werror
NAME 			= minishell

READLINE_LIB 	= -lreadline -L/usr/local/opt/readline/lib
READLINE_INC	= -I/usr/local/opt/readline/include

LIBFT		= libft.a
LIBFT_DIR	= libft

SRC_DIR 	= srcs
SRC 		= srcs/utils/utils.c \
			  srcs/execute/exec.c srcs/utils/error_management.c \
			  srcs/execute/ft_cd.c srcs/execute/ft_exit.c \
			  srcs/execute/ft_env.c srcs/execute/ft_pwd.c \
			  srcs/execute/ft_export.c srcs/execute/export_utils.c \
			  srcs/redirection/redir_chk.c \
			  srcs/redirection/redirect.c srcs/redirection/redirect_check.c \
			  srcs/execute/ft_echo.c srcs/execute/ft_unset.c \
			  srcs/execute/exec_utils.c srcs/utils/utils2.c \
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
