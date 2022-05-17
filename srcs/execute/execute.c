/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:43:23 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/17 21:48:31 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 
int		is_redirection(char *cmd)
{
	if (ft_strncmp(cmd, ">", 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "<", 1) == 0)
		return (1);
	if (ft_strncmp(cmd, ">>", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "<<", 2) == 0)
		return (1);
	return (0);
}

int	get_cmd_size(t_cmd *cmd_list)
{
	int	i;

	i = 0;

	while (cmd_list->cmdline[i].cmd)
		i++;
	return (i);
}

char	**bind_cmd(t_token *cmdline)
{
	int		i;
	int		len;
	char	**cmd_arg;

	
	len = 0;
	while (cmdline[len].cmd)
		len++;
	cmd_arg = (char **)malloc(sizeof(char *) * (len + 1));
	if (!cmd_arg)
		return (NULL);
	i = -1;
	while (cmdline[++i].cmd)
		cmd_arg[i] = ft_strdup(cmdline[i].cmd);
	cmd_arg[i] = NULL;
	return (cmd_arg);
}

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
		dup2(cmd_list->pip[1], STDOUT);
		close(cmd_list->pip[1]);
		close(cmd_list->pip[0]);
		cmd_argv = bind_cmd(cmd_list->cmdline);
		if (execve(cmd, cmd_argv, *env) == -1)
			exit(127);
	}
	else
	{
		dup2(cmd_list->pip[0], STDIN);
		close(cmd_list->pip[1]);
		close(cmd_list->pip[0]);
		waitpid(pid, &cmd_list->status, 0);
	}
}

void	execute_builtin_pipe(t_cmd *cmd_list, char ***env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(cmd_list->pip[1], STDOUT);
		close(cmd_list->pip[1]);
		close(cmd_list->pip[0]);
		exit(exec_builtin(cmd_list, env));
	}
	else
	{
		dup2(cmd_list->pip[0], STDIN);
		close(cmd_list->pip[1]);
		close(cmd_list->pip[0]);
		waitpid(pid, &cmd_list->status, 0);
	}
}

void	execute_builtin(t_cmd *cmd_list, char ***env, int stdin_dup, int stdout_dup)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(cmd_list->pip[0]);
		close(cmd_list->pip[1]);
		exit(exec_builtin(cmd_list, env));
	}
	else
	{
		close(cmd_list->pip[0]);
		close(cmd_list->pip[1]);
		waitpid(pid, NULL, 0);
		dup2(stdin_dup, 0);
		dup2(stdout_dup, 1);
		close(stdin_dup);
		close(stdout_dup);
	}
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
		dup2(stdin_dup, 0);
		dup2(stdout_dup, 1);
		close(stdin_dup);
		close(stdout_dup);
	}
}

void	execute(t_cmd *cmd_list, char ***env)
{
	int		i;
	int		stdin_dup;
	int		stdout_dup;
	
	stdin_dup = dup(0);
	stdout_dup = dup(1);
	while (cmd_list)
	{	
		pipe(cmd_list->pip);	
		if (cmd_list->pipe_flag)
		{	
			if (is_builtin(cmd_list->cmdline[0].cmd))
				execute_builtin_pipe(cmd_list, env);
			else
				execute_cmd_pipe(cmd_list, env);
		}
		else
		{
			if (is_builtin(cmd_list->cmdline[0].cmd))
				execute_builtin(cmd_list, env, stdin_dup, stdout_dup);
			else
				execute_cmd(cmd_list, env, stdin_dup, stdout_dup);
		}
		cmd_list = cmd_list->next;
	}	
	return ;
}
