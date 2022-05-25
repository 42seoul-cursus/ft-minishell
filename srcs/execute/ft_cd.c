/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:08:52 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/25 20:22:50 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_chdir(char ***env, char *path)
{
	char	old_pwd[1024];
	char	current_pwd[1024];

	if (!getcwd(old_pwd, 1024))
		return (EXIT_FAILURE);
	if (check_dir(path) == -1)
	{
		ft_putstr_fd("cd: ", STDERR);
		ft_putstr_fd(path, STDERR);
		ft_putendl_fd(": Permission denied", STDERR);
		return (EXIT_FAILURE);
	}
	if (chdir(path) == -1)
	{
		print_cd_error(path);
		return (EXIT_FAILURE);
	}
	if (!getcwd(current_pwd, 1024))
		return (EXIT_FAILURE);
	return (add_cd_env(current_pwd, old_pwd, env));
}

int	execute_env(t_cmd *cmd_list, char ***env, char *home, char *path)
{	
	int	is_error;

	is_error = EXIT_FAILURE;
	path = cmd_list->cmdline[1].cmd;
	if (path != NULL && ft_strlen(path) == 0)
		is_error = execute_chdir(env, home);
	else
		is_error = execute_chdir(env, path);
	return (is_error);
}

int	execute_none_option(t_cmd *cmd_list, char ***env, char *home)
{
	int	is_error;

	is_error = EXIT_FAILURE;
	if (get_cmd_size(cmd_list) <= 1)
		is_error = execute_chdir(env, home);
	return (is_error);
}

int	execute_home(t_cmd *cmd_list, char ***env, char *home, char *path)
{
	int	is_error;

	is_error = EXIT_FAILURE;
	if (cmd_list->cmdline[1].cmd[0] == '~')
	{
		path = ft_strjoin(home, cmd_list->cmdline[1].cmd + 1);
		if (ft_strlen(cmd_list->cmdline[1].cmd) == 1)
			is_error = execute_chdir(env, home);
		else
			is_error = execute_chdir(env, path);
	}
	if (path)
		free(path);
	return (is_error);
}

int	ft_cd(t_cmd *cmd, char ***env)
{
	char	*home;
	char	*path;
	int		is_error;

	home = getenv("HOME");
	path = NULL;
	if (get_cmd_size(cmd) == 1)
		is_error = execute_none_option(cmd, env, home);
	else if (cmd->cmdline[1].cmd[0] == '~')
		is_error = execute_home(cmd, env, home, path);
	else
		is_error = execute_env(cmd, env, home, path);
	return (is_error);
}
