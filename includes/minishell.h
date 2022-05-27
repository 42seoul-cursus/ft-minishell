/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:57:07 by jeonghwl          #+#    #+#             */
/*   Updated: 2022/05/27 20:32:37 by hkim2            ###   ########.fr       */
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
# include <string.h>

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

# define HEREDOC ".heredoc_tmp"

typedef struct s_token
{
	char	*cmd;
	char	redir_flag;
}	t_token;

typedef struct s_cmd
{
	t_token			*cmdline;
	struct s_cmd	*next;
	int				pip[2];
	int				status;
	int				pipe_flag;
	char			redir_flag;
	int				right_flag;
	int				prev_pipe_flag;
	char			quote;
	char			*path;
	char			**env;
}	t_cmd;

typedef struct s_token_quote_status
{
	int	token_index;
	int	quote;
}	t_token_quote_status;

int					ft_redir_chk(char *str);

//signal.c
void				ft_signal(void);

// parser/print_termianl.c
char				*ft_strjoin_location(char *s1, char const *s2);
void				ft_print_title(int argc);
char				*ft_init_location(void);

//parser/assign_command.c
t_cmd				*ft_assign_command(char *line, int pipe_flag, char **envp, \
						int exit_flag);
// parser/assign_output_command.c
t_token				*ft_assign_output_command(t_token *token, char **envp);

// parser/assign_output_token.c
void				*ft_assign_output_token(char *input_token, \
						char *output_token, char **envp);
int					ft_if_question(char *input_token, \
						char ***output_token, char **envp);
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
int					execute(t_cmd *cmd_list, char ***env);
void				execute_cmd_pipe(t_cmd *cmd_list, char ***env, \
						int stdout_dup);
void				execute_builtin_pipe(t_cmd *cmd_list, char ***env, \
						int stdout_dup);
int					execute_builtin(t_cmd *cmd_list, char ***env, \
						int stdin_dup, int stdout_dup);
void				execute_cmd(t_cmd *cmd_list, char ***env, \
						int stdin_dup, int stdout_dup);

//execute/execute_util.c
int					check_path(t_cmd *cmd_list, char ***path, \
						char **cmd, char **env);
int					get_cmd_size(t_cmd *cmd_list);
char				**bind_cmd(t_token *cmdline);
void				exec_pipe(t_cmd *cmd_list, char ***env, \
						int stdin_dup, int stdout_dup);
void				exec_without_pipe(t_cmd *cmd_list, char ***env, \
						int stdin_dup, int stdout_dup);

//execute/execute_error
void				close_pipe(t_cmd *cmd_list);
void				print_execute_error(char *cmd, int error_code);
void				set_child_process_status(t_cmd *cmd_list, char ***env);
int					is_redirection(char *cmd);

//execute/env_util.c
char				**get_cmd_path(char **env);
char				*get_cmd(char **path, char *cmd, int *status);
int					find_cmd_index(char **path, char *cmd);
char				*check_completed_cmd(char *cmd);
void				init_env(char ***env);

//execute/execute_builtin.c
int					is_builtin(char *cmd);
int					exec_builtin(t_cmd *cmd_list, char ***env);

//execute/ft_pwd.c
int					ft_pwd(t_cmd *cmd_list);

//execute/ft_env.c
int					ft_env(char **env);
void				sort_env(char ***env);

//execute/ft_export.c
int					ft_export(t_cmd *cmd_list, char ***env);
int					print_export(char **env);
void				free_split_str(char **str);
void				print_export_error(char *cmd);
int					add_env(char *cmd, char ***env);

//execute/export_util
void				free_split_str(char **str);
int					is_vaild_word(char c);
int					add_duplicate_key(char *cmd, char ***env);
int					get_duplicate_index(char *cmd, char **env);
int					add_new_value(char *cmd, char ***env);

//execute/ft_unset.c
int					ft_unset(t_cmd *cmd_list, char ***env);
void				print_unset_error(char *cmd);
int					valid_unset_cmd(char *cmd);
int					get_removal_index(char *cmd, char **env);
void				remove_env(char *cmd, char ***env);

//execute/ft_cd.c
int					ft_cd(t_cmd *cmd_list, char ***env);
int					execute_chdir(char ***env, char *path);
int					execute_env(t_cmd *cmd_list, char ***env, \
						char *home, char *path);
int					execute_none_option(t_cmd *cmd_list, \
						char ***env, char *home);
int					execute_home(t_cmd *cmd_list, char ***env, \
						char *home, char *path);

//execute/ft_cd_util.c
int					print_cd_error(char *cmd);
int					add_cd_env(char *current_pwd, char *old_pwd, char ***env);
int					check_dir(char *path);
int					check_file(char *path);

//execute/ft_echo.c
int					ft_echo(t_cmd *cmd_list);
void				print_echo(t_cmd *cmd_list);
void				print_echo_no_newline(t_cmd *cmd_list);
int					check_newline(char *cmd);

//execute/ft_exit.c
int					ft_exit(t_cmd *cmd_list);
int					execute_exit(t_cmd *cmd_list);
void				print_exit_many_arg(void);
void				print_exit_numeric(char *cmd);
int					is_numeric(char *cmd);

//execute/ft_exit_util.c
int					is_space(char c);
long long			ft_atoi2(const char *str);

//execute/redirection.c
int					redirewction_out(t_cmd *ccmd_list, int i);
int					redirection_in(t_cmd *ccmd_list, int i);
int					redirection_out_append(t_cmd *ccmd_list, int i);
int					redirection_heredoc(t_cmd *ccmd_list, int i, \
						int in, int out);
int					set_redirection(t_cmd *ccmd_list, int i, int in, int out);

//execute/redirection_util.c
int					parse_cmd_without_ridir(t_cmd *cmd_list, \
						int non_redir_count);
int					check_redirection(t_cmd *cmd_list, \
						int in, int out);
int					pre_check(t_cmd *cmd_list, char ***env, \
						int stdin_dup, int stdout_dup);
int					print_syntax_error(void);

//execute/redirection_util_two.c
void				pre_init(t_cmd *cmd_list);
int					check_pipe_syntax(t_cmd *cmd_list);
void				check_prev_pipe(t_cmd *cmd_list);
int					print_file_error(char *filename);

//execute/redirection_util_fd.c
int					read_heredoc(t_cmd *cmd_list, char *str, int i);
void				set_dup2(int in, int out);
void				set_stdin(int fd);

//execute/pipe_util.c
void				set_std_descriptor(int stdin_dup, int stdout_dup);

//execute/error_status.c
void				set_error_status(char ***env, int status);
void				set_parent_process_status(t_cmd *cmd_list, char ***env);

#endif
