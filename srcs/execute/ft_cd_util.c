/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:00:07 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/27 20:18:12 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_cd_error(char *cmd)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putendl_fd(cmd, 2);
	return (EXIT_FAILURE);
}

int	add_cd_env(char *current_pwd, char *old_pwd, char ***env)
{
	char	*env_pwd;
	char	*env_old_pwd;

	env_pwd = ft_strjoin("PWD=", current_pwd);
	if (!env_pwd)
		return (EXIT_FAILURE);
	env_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	if (!env_old_pwd)
		return (EXIT_FAILURE);
	if (add_env(env_pwd, env) || add_env(env_old_pwd, env))
	{
		ft_putendl_fd("cd : set env error", 2);
		if (env_old_pwd)
			free(env_old_pwd);
		if (env_pwd)
			free(env_pwd);
	}
	free(env_old_pwd);
	free(env_pwd);
	return (EXIT_SUCCESS);
}

int	check_dir(char *path)
{
	struct stat	file_info;

	if (stat(path, &file_info) == -1)
		return (EXIT_FAILURE);
	if (S_ISDIR(file_info.st_mode))
	{
		if (!(file_info.st_mode & S_IXUSR))
			return (-1);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	check_file(char *path)
{
	struct stat	file_info;

	if (stat(path, &file_info) == -1)
		return (EXIT_FAILURE);
	if (S_ISREG(file_info.st_mode))
	{
		if (!(file_info.st_mode & S_IXUSR))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
