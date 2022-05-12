/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:58:49 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/12 18:24:55 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	free_split_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	print_export(char **env)
{
	int		i;
	char	**split;

	i = 0;
	int j = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (!split)
			continue;
		printf("declare -x %s=", split[0]);
		if (split[1])
			printf("\"%s\"", split[1]);
		else
			printf("\"\"");
		printf("\n");
		i++;
		free_split_str(split);
	}
}

/*
명령어를 하나의 문자열로 만든다.
a=b
a = b

*/
char	*bind_cmds(t_cmd *cmd_list)
{
	int		i;
	int		len;
	char	*str;
	int		count;
	int		j;

	i = 1;
	len += get_cmd_size(cmd_list) - 2 + 1;
	while (cmd_list->cmdline[i].cmd)
		len += ft_strlen(cmd_list->cmdline[i++].cmd);
	str = malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	i = 0;
	count = 0;
	while (++i < (get_cmd_size(cmd_list)))
	{
		j = 0;
		while (j < ft_strlen(cmd_list->cmdline[i].cmd))
			str[count++] = cmd_list->cmdline[i].cmd[j++];
		str[count++] = ' ';	
	}
	str[count - 1] = NULL;
	return (str);
}

int	validate_export(char *cmd)
{
	//한 개 씩 파씽!!
}
int	ft_export(t_cmd *cmd_list, char **env)
{
	char	*cmd;
	int		ret;
	int		i;

	ret = 0;
	if (get_cmd_size(cmd_list) == 1)
	{
		print_export(env);
		return (EXIT_SUCCESS);
	}
	i = 1;
	
	while (cmd_list->cmdline[i].cmd)
	{
		cmd = bind_cmds(cmd_list);
		if (!cmd)
			return (EXIT_FAILURE);

	}
}