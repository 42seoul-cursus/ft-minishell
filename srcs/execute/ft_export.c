/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:58:49 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/12 21:53:18 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(char **env)
{
	int		i;
	char	**split;

	i = 0;
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

void	print_export_error(char *cmd)
{
	ft_putstr_fd("export: not an identifier: ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("'\n", 2);
}

void	add_env(char *cmd, char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
		i++;
	(*env)[i] = ft_strdup(cmd);
	(*env)[i + 1] = NULL;
}

int	valid_cmd(char *cmd)
{
	char	*tmp;
	int		i;
	int		len;
	
	if (!ft_isalpha(cmd[0]))
		return (EXIT_FAILURE);
	tmp = ft_strchr(cmd, '=');
	if (!tmp)
		len = ft_strlen(cmd);
	else
		len = tmp - cmd;
	i = 0;
	while (i < len)
		if (!ft_isalnum(cmd[i++]))
			return EXIT_FAILURE;
	return (EXIT_SUCCESS);
}

int	ft_export(t_cmd *cmd_list, char ***env)
{
	char	*cmd;
	int		is_error;
	int		i;
	
	is_error = EXIT_SUCCESS;
	if (get_cmd_size(cmd_list) == 1)
	{
		print_export(*env);
		return (EXIT_SUCCESS);
	}
	i = 0;
	while (cmd_list->cmdline[++i].cmd)
	{
		cmd = ft_strdup(cmd_list->cmdline[i].cmd);
		if (!cmd)
			return (EXIT_FAILURE);
		if (valid_cmd(cmd))
		{
			print_export_error(cmd);
			is_error = EXIT_SUCCESS;
		}
		else
			add_env(cmd, env);
		free(cmd);
	}
	return (is_error);
}