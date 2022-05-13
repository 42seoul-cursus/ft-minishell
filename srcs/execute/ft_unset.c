/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:12:29 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/13 19:04:48 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	print_unset_error(char *cmd)
{
	ft_putstr_fd("unset: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" invalid parameter name\n", 2);
}

int	valid_unset_cmd(char *cmd)
{
	int		i;
	int		len;
	
	if (!is_vaild_word(cmd[0]))
		return (EXIT_FAILURE);
	len = ft_strlen(cmd);
	i = 1;
	while (i < len)
	{
		if (!is_vaild_word(cmd[i]) && !ft_isdigit(cmd[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}


void	remove_env(char *cmd, char ***env)
{
	char	**tmp;
	int		i;
	int		len;
	int		re_index;

	len = 0;
	while ((*env)[len])
		len++;
	tmp = (char **)malloc(sizeof(char *) * len);
	i = -1;
	len = 0;
	re_index = get_removal_index(cmd, *env);	
	while ((*env)[++i])
	{
		if (re_index == i)
			continue;
		tmp[len++] = ft_strdup((*env)[i]);
	}
	tmp[len] = NULL;
	i = 0;
	while ((*env)[i])
		free((*env)[i++]);
	free(*env);
	(*env) = tmp;
}

int	get_removal_index(char *cmd, char **env)
{
	int		i;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (!split)
			return (-1);
		if (ft_strlen(split[0]) == ft_strlen(cmd))
		{
			if (ft_strncmp(split[0], cmd, ft_strlen(cmd)) == 0)
				return (i);
		}
		free_split_str(split);
		i++;
	}
	return (-1);
}

int	ft_unset(t_cmd *cmd_list, char ***env)
{
	char	*cmd;
	int		i;
	int		is_error;
	
	is_error = EXIT_SUCCESS;
	if (get_cmd_size(cmd_list) == 1)
		return (EXIT_SUCCESS);
	i = 1;
	while (cmd_list->cmdline[i].cmd)
	{
		cmd = ft_strdup(cmd_list->cmdline[i].cmd);
		if (!cmd)
			return (EXIT_FAILURE);
		if (valid_unset_cmd(cmd))
		{
			print_unset_error(cmd);
			is_error = EXIT_FAILURE;
		}
		else if (get_removal_index(cmd, *env) != -1)
			remove_env(cmd, env);
		i++;
	}
	return (is_error);
}
