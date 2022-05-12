/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:57:07 by jeonghwl          #+#    #+#             */
/*   Updated: 2022/05/12 21:52:31 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include <signal.h>

# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2

# define QUOTE 0
# define END 1

# define CLOSE 0
# define OPEN 1

# define YES 0
# define NO 1

# define BREAK 1
# define CONTINUE 0

# define CLOSED 1
# define UNCLOSED 0

extern int	g_exit_status;

typedef struct s_arg
{
	char	**argv;
	char	**envp;
}	t_arg;

typedef struct s_nbf
{
	struct stat	*buf;
	char		*env_path;
	char		**paths;
	int			flag;
}	t_nbf;

typedef struct s_err
{
	int		errcode;
	int		errindex;
	char	*errtoken;
}	t_err;

typedef struct s_token
{
	char	*cmd;
	char	redir_flag;
}	t_token;

typedef struct s_cmd
{
	t_token			*cmdline;
	struct s_err	err_manage;
	struct s_cmd	*next;
	int				pipe_flag;
	int				exit_flag;
	int				right_flag;
	char			quote;
	char			*path;
	char			**env;
	char			*(redirect_filename[4]);
}	t_cmd;

typedef struct s_token_quote_status
{
	int	token_index;
	int	quote;
}	t_token_quote_status;

//char				check_quote(char *line);

//int					exec(t_cmd *cmp_list, char *argv[], char **envp[]);
//int					exec_function(t_cmd *cmd_list, char *argv[], char **envp[], \
//					int fds[]);

//void				init_nbf(t_nbf *nbf);
//int					free_nbf(t_nbf *nbf);
//int					check_redirect(t_cmd *cmd_list, int fds[]);
//void				exec_child(t_cmd *cmd_list, char *argv[], char **envp[], \
//					int fds[]);
//int					exec_parents(int pid, int fds[]);

//char				*ft_join_path(char const *s1, char const *s2);

//int					ft_cd(t_cmd *cmd_list);
//int					ft_exit(t_cmd *cmd_list);
//int					ft_pwd(int fd);
//int					ft_echo(t_cmd *cmd_list, int fd);
//int					ft_env(t_cmd *cmd_list, char **envp, int fd);
//int					ft_export(t_cmd *cmd_list, char ***envp, int fd);

//void				print_errstr(t_cmd *cmd_list);
//void				error_write(char *error_str,
//						char *err_cmdline, char *err_cmdline2);
//void				print_errstr3(t_cmd *cmd_list);

//int					add_envp(char *cmd, char ***envp);
//int					isvalid_export(char *line);
//int					cnt_envp_row(char **envp);
//char				**sort_env(char **envp);
//int					haveequal(char *line);
//void				add_key_envp(char ***envp, char *cmd, int keyindex);

//int					redirect(t_cmd *cmd_list, int *last_index, int *fds[]);
//int					redirect_check(t_cmd *cmd_list, int *fds[]);
//int					check_fd_error(t_cmd *cmd_list, int errorcode, \
//					int error_index, int fd);

int					ft_redir_chk(char *str);
//int					redir_err_chk(t_cmd *cmd_list);

//int					ft_valid_key(char *key);
//int					ft_unset(t_cmd *cmd_list, char **envp);

//signal.c
void				ft_signal(void);

// parser/print_termianl.c
char				*ft_strjoin_location(char *s1, char const *s2);
void				ft_print_title(void);
char				*ft_init_location_and_dup2(void);

//parser/assign_command.c
t_cmd				*ft_assign_command(char *line, int pipe_flag, char **envp, \
					int exit_flag);
// parser/assign_output_command.c
t_token				*ft_assign_output_command(t_token *token, char **envp);

// parser/assign_output_token.c
void				*ft_assign_output_token(char *input_token, \
					char *output_token, char **envp);
int					ft_if_question(char *input_token, char ***output_token);
int					ft_if_null_or_d_quote(char *input_token, \
					char ***output_token);
void				ft_if_redir_in_token(t_token *token);

// parser/command_split.c
t_token				*ft_command_split(char const *s, char c);

// parser/env_init_key_value.c
int					ft_env_key(char *src, char **key);
int					ft_env_key_len(char *token);
char				*ft_env_value(char *key, char **envp);
int					ft_env_value_len(char *token, int key_len, char **envp);
char				**ft_init_env(char **envs);

//parser/get_token.
char				*ft_get_token(int *next_index, char const *command, \
						const char c);

//parser/output_token_len.c
int					ft_output_token_len(char *str, char **envp);
int					ft_is_closed_quote(char *str, char quote);

// parser/parse.c
void				ft_parse(t_cmd **cmd_list, char *line, char **envp);

//execute header

//execute/execute.c
void				execute(t_cmd *cmd_list, char ***env);
int					is_redirection(char *cmd);
int					get_cmd_size(t_cmd *cmd_list);

//execute/env_util.c
char				**get_cmd_path(char **env);
char				*get_cmd(char **path, char *cmd);
int					find_cmd_index(char **path, char *cmd);
int					check_file(char *path);
int					check_dir(char *path);

//execute/execute_builtin.c
int					is_builtin(char *cmd);
int					exec_builtin(t_cmd *cmd_list, char ***env);

//execute/ft_pwd.c
int					ft_pwd(t_cmd *cmd_list);

//execute/ft_env.c
int					ft_env(char **env);

//execute/ft_export.c
int					ft_export(t_cmd *cmd_list, char ***env);
void				print_export(char **env);
void				free_split_str(char **str);
void				print_export_error(char *cmd);
void				add_env(char *cmd, char ***env);

//execute/export_util
void				free_split_str(char **str);
#endif
