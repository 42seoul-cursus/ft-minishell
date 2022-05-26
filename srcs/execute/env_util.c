/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:14:40 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/25 19:49:14 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_cmd_path(char **env)
{
	int		i;
	char	**path;
	char	*get_path;

	get_path = getenv("PATH");
	if (!get_path)
		return (NULL);
	path = ft_split(get_path, ':');
	if (path)
		return (path);
	return (NULL);
}

char	*check_completed_cmd(char *cmd)
{
	struct stat	file_info;

	if (stat(cmd, &file_info))
		return (NULL);
	if (S_ISREG(file_info.st_mode))
		return (cmd);
	return (NULL);
}

char	*get_cmd(char **path, char *cmd)
{
	int		cmd_idx;
	char	*add_slash_cmd;
	char	*path_cmd;

	if (check_completed_cmd(cmd))
		return (cmd);
	add_slash_cmd = ft_strjoin("/", cmd);
	if (!add_slash_cmd)
		return (NULL);
	cmd_idx = find_cmd_index(path, add_slash_cmd);
	if (cmd_idx < 0)
		return (NULL);
	path_cmd = ft_strjoin(path[cmd_idx], add_slash_cmd);
	if (!path_cmd)
		return (NULL);
	free(add_slash_cmd);
	return (path_cmd);
}

int	find_cmd_index(char **path, char *cmd)
{
	int			i;
	char		*str;
	struct stat	file_info;

	i = -1;
	while (path[++i])
	{
		str = ft_strjoin(path[i], cmd);
		if (stat(str, &file_info))
			continue ;
		if (S_ISREG(file_info.st_mode))
		{
			if (!(file_info.st_mode & S_IXUSR))
			{
				printf("%s Permission denied", str);
				exit(126);
			}
			return (i);
		}
	}
	return (-1);
}

void	init_env(char ***env)
{
	char		*str;
	long long	level;

	str = getenv("SHLVL");
	if (!str)
	{
		add_env("SHLVL=1", env);
		return ;
	}
	level = ft_atoi(str, NULL);
	level++;
	str = ft_strjoin("SHLVL=", ft_itoa((int)level));
	add_env(str, env);
	free(str);
	str = ft_strjoin("ERROR_STATUS=", ft_itoa(0));
	add_env(str, env);
	free(str);
}
