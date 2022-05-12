/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:14:40 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/12 18:25:16 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
환경 변수 "PATH" 부분을 ':' 구분자로 split
각각 구분된 문자열은 명령어들이 있는 디렉토리를 의미함
성공 - 문자열 배열 반환
실패 - NULL 반환
*/
char	**get_cmd_path(char **env)
{
	int	i;
	char	**path;
	char	*get_path;

	//i = 0;
	//while(env[i])
	//{	
	//	if (ft_strncmp(env[i], "PATH=", 5) == 0)
	//		break;
	//	i++;
	//}
	//if (env[i] == NULL)
	//	return (NULL);
	get_path = getenv("PATH");
	if (!get_path)
		return (NULL);
	path = ft_split(get_path, ':');
	if (path)
		return (path);
	return (NULL);
}


/*
첫 번째 인자로 명령어가 있는 디렉토리, 두 번째 인자로 명령어를 받고
명령어에 '/'를 붙여 디렉토리에 해당 명령어가 있는지 검사한다.
ex)
디렉토리 : "/bin"
명령어 : "ls"
/를 붙여 합치면 "/bin/ls"이 나오고 해당 파일을 검사한다.
성공 - 실행할 명령어의 절대경로
실패 - NULL
*/
char	*get_cmd(char **path, char *cmd)
{
	int		cmd_idx;
	char	*add_slash_cmd;
	char	*path_cmd;

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

/*
첫 번째 인자로 들어온 명령어가 있는 디렉토리 목록(path)에서
두 번째 인자로 들어온 명령어(cmd)가 실행 가능한 명령어 인지 확인
성공 - 디렉토리 목록 중 해당 명령어가 있는 index 반환
실패 - -1 반환
*/
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
				continue;
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

int	check_dir(char *path)
{
	struct stat	file_info;

	if (stat(path, &file_info) == -1)
		return (EXIT_FAILURE);
	if (S_ISDIR(file_info.st_mode))
	{
		if (!(file_info.st_mode & S_IXUSR))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}