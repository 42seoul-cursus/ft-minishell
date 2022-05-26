/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:43:23 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/27 02:16:25 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_cmd_pipe(t_cmd *cmd_list, char ***env, int stdin_dup, int stdout_dup)
{
	char	**path;
	char	*cmd;
	char	**cmd_argv;
	pid_t	pid;

	path = get_cmd_path(*env);
	cmd = get_cmd(path, cmd_list->cmdline[0].cmd);
	pid = fork();
	if (pid == 0)
	{
		if (!cmd_list->right_flag)
			dup2(cmd_list->pip[1], STDOUT_FILENO);
		close_pipe(cmd_list);
		cmd_argv = bind_cmd(cmd_list->cmdline);
		execve(cmd, cmd_argv, *env);
		print_execute_error(cmd_list->cmdline[0].cmd, 127);
	}
	else
	{
		if (cmd_list->right_flag)
			dup2(stdout_dup, STDOUT_FILENO);
		dup2(cmd_list->pip[0], STDIN_FILENO);
		waitpid(pid, &cmd_list->status, 0);
		close_pipe(cmd_list);
		set_child_process_status(cmd_list, env);
	}
}

void	execute_builtin_pipe(t_cmd *cmd_list, char ***env, int stdin_dup, int stdout_dup)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (cmd_list->right_flag)
			exit(exec_builtin(cmd_list, env));
		else
		{
			dup2(cmd_list->pip[1], STDOUT_FILENO);
			close_pipe(cmd_list);
			exit(exec_builtin(cmd_list, env));
		}
	}
	else
	{
		if (cmd_list->right_flag)
			dup2(stdout_dup, STDOUT_FILENO);
		dup2(cmd_list->pip[0], STDIN_FILENO);
		close_pipe(cmd_list);
		waitpid(pid, &cmd_list->status, 0);
	}
}

int	execute_builtin(t_cmd *cmd_list, char ***env, int stdin_dup, int stdout_dup)
{
	int	is_error;

	is_error = exec_builtin(cmd_list, env);
	set_std_descriptor(stdin_dup, stdout_dup);
	return (is_error);
}

void	execute_cmd(t_cmd *cmd_list, char ***env, int stdin_dup, int stdout_dup)
{
	char	**path;
	char	*cmd;
	char	**cmd_argv;
	pid_t	pid;

	path = get_cmd_path(*env);
	cmd = get_cmd(path, cmd_list->cmdline[0].cmd);
	pid = fork();
	if (pid == 0)
	{
		close_pipe(cmd_list);
		cmd_argv = bind_cmd(cmd_list->cmdline);
		execve(cmd, cmd_argv, *env);
		print_execute_error(cmd_list->cmdline[0].cmd, 127);
	}
	else
	{
		close_pipe(cmd_list);
		set_std_descriptor(stdin_dup, stdout_dup);
		waitpid(pid, &cmd_list->status, 0);
		set_child_process_status(cmd_list, env);
	}
}

int	execute(t_cmd *cmd_list, char ***env)
{
	int		stdin_dup;
	int		stdout_dup;

	stdin_dup = dup(0);
	stdout_dup = dup(1);
	pre_init(cmd_list);
	while (cmd_list)
	{	
		pipe(cmd_list->pip);
		if (pre_check(cmd_list, env, stdin_dup, stdout_dup))
			return (EXIT_FAILURE);
		if (cmd_list->pipe_flag)
			exec_pipe(cmd_list, env, stdin_dup, stdout_dup);
		else
			exec_without_pipe(cmd_list, env, stdin_dup, stdout_dup);
		cmd_list = cmd_list->next;
	}	
	return (EXIT_SUCCESS);
}
