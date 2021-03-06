# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/12 14:11:43 by jeonghwl          #+#    #+#              #
#    Updated: 2022/05/27 20:30:24 by hkim2            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC 				= gcc
RM				= rm -rf
#-Werror을 하면 not uses가 떠서 잠시 주석처리
CFLAGS 			= -Wall -Wextra -g -fsanitize=address -Werror
NAME 			= minishell

READLINE_LIB 	= -lreadline -L/usr/local/opt/readline/lib
READLINE_INC	= -I/usr/local/opt/readline/include

LIBFT		= libft.a
LIBFT_DIR	= libft

SRC_DIR 	= srcs
SRC 		= srcs/minishell.c \
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
					srcs/execute/ft_exit_util.c \
					srcs/execute/redirection.c \
					srcs/execute/redirection_util.c \
					srcs/execute/pipe_util.c \
					srcs/execute/execute_error.c \
					srcs/execute/error_status.c \
					srcs/execute/redirection_util_two.c \
					srcs/execute/redirection_util_fd.c \
				
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
