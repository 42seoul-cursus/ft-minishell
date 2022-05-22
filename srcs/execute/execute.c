/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:43:23 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/22 19:07:45 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 


/*
리다이렉션 처리가 이미 됐다고 가정
*/
void	execute_cmd_pipe(t_cmd *cmd_list, char ***env)
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
		dup2(cmd_list->pip[1], STDOUT_FILENO);
		close(cmd_list->pip[1]);
		close(cmd_list->pip[0]);
		cmd_argv = bind_cmd(cmd_list->cmdline);
		if (execve(cmd, cmd_argv, *env) == -1)
			exit(127);
	}
	else
	{
		dup2(cmd_list->pip[0], STDIN_FILENO);
		close(cmd_list->pip[1]);
		close(cmd_list->pip[0]);
		waitpid(pid, &cmd_list->status, 0);
	}
}

void	execute_builtin_pipe(t_cmd *cmd_list, char ***env, int stdin_dup, int stdout_dup)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (cmd_list->redir_flag)
		{
			exec_builtin(cmd_list, env);
			dup2(stdout_dup, STDOUT_FILENO);
			close(stdout_dup);
			close(cmd_list->pip[1]);
			close(cmd_list->pip[0]);
		}
		else
		{
			dup2(cmd_list->pip[1], STDOUT_FILENO);
			close(cmd_list->pip[1]);
			close(cmd_list->pip[0]);
			exit(exec_builtin(cmd_list, env));
		}
	}
	else
	{
		dup2(cmd_list->pip[0], STDIN_FILENO);
		close(cmd_list->pip[1]);
		close(cmd_list->pip[0]);
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
		close(cmd_list->pip[0]);
		close(cmd_list->pip[1]);
		cmd_argv = bind_cmd(cmd_list->cmdline);
		if (execve(cmd, cmd_argv, *env) == -1)
			exit(127);
	}
	else
	{
		close(cmd_list->pip[1]);
		close(cmd_list->pip[0]);
		waitpid(pid, &cmd_list->status, 0);
		set_std_descriptor(stdin_dup, stdout_dup);
	}
}

int	execute(t_cmd *cmd_list, char ***env)
{
	int		stdin_dup;
	int		stdout_dup;
	
	stdin_dup = dup(0);
	stdout_dup = dup(1);
	
	while (cmd_list)
	{	
		if (!cmd_list->cmdline[0].cmd)
			return (0);
		cmd_list->redir_flag = 0;
		pipe(cmd_list->pip);
		if (pre_check(cmd_list, stdin_dup, stdout_dup))
			return (EXIT_FAILURE);
		if (cmd_list->pipe_flag)
			if (is_builtin(cmd_list->cmdline[0].cmd))
				execute_builtin_pipe(cmd_list, env, stdin_dup, stdout_dup);
			else
				execute_cmd_pipe(cmd_list, env);
		else
		{
			if (is_builtin(cmd_list->cmdline[0].cmd))
				execute_builtin(cmd_list, env, stdin_dup, stdout_dup);
			else
				execute_cmd(cmd_list, env, stdin_dup, stdout_dup);
		}
		cmd_list = cmd_list->next;
	}	
	return (EXIT_SUCCESS);
}
