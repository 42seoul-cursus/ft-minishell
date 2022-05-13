/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:58:49 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/13 18:59:01 by hkim2            ###   ########.fr       */
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

int	add_env(char *cmd, char ***env)
{
	int		i;
	char	**tmp;
	int		len; 
	
	if (!add_duplicate_key(cmd, env))
		return (EXIT_FAILURE);
	len = 0;
	i = 0;
	while ((*env)[len])
		len++;
	tmp = (char **)malloc(sizeof(char *) * len + sizeof(char *) * 2);
	i = 0;
	while (i < len)
	{
		tmp[i] = ft_strdup((*env)[i]);
		i++;
	}
	tmp[len] = ft_strdup(cmd);
	tmp[len + 1] = NULL;
	free(*env);
	(*env) = tmp;
	return (EXIT_SUCCESS);
}

int	valid_cmd(char *cmd)
{
	char	*tmp;
	int		i;
	int		len;
	
	if (!is_vaild_word(cmd[0]))
		return (EXIT_FAILURE);
	tmp = ft_strchr(cmd, '=');
	if (!tmp)
		len = ft_strlen(cmd);
	else
		len = tmp - cmd;
	i = 1;
	while (i < len)
	{
		if (!is_vaild_word(cmd[i]) && !ft_isdigit(cmd[i]))
			return EXIT_FAILURE;
		i++;
	}
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