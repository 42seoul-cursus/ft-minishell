/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:00:07 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/14 00:00:21 by hkim2            ###   ########.fr       */
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
	add_env(env_pwd, env);
	add_env(env_old_pwd, env);
	free(env_old_pwd);
	free(env_pwd);
	return (EXIT_SUCCESS);
}