/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:43:58 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/18 17:02:12 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

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

int	is_vaild_word(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int	get_duplicate_index(char *cmd, char **env)
{
	int		i;
	char	**split;
	char	**split_cmd;

	split_cmd = ft_split(cmd, '=');
	if (!split_cmd)
		return (-1);
	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (!split)
			return (-1);
		if (ft_strlen(split[0]) == ft_strlen(split_cmd[0]))
			if (ft_strncmp(split[0], split_cmd[0], ft_strlen(split_cmd[0])) == 0)
				return (i);
		i++;
	}
	return (-1);
}

int	add_duplicate_key(char *cmd, char ***env)
{
	char	*tmp;
	int		key_index;

	key_index = get_duplicate_index(cmd, *env);
	if (key_index == -1)
		return (-1);
	tmp = ft_strdup(cmd);
	if (!tmp)
		return (EXIT_FAILURE);
	free((*env)[key_index]);
	(*env)[key_index] = tmp;
	return (EXIT_SUCCESS);
}

int	add_new_value(char *cmd, char ***env)
{
	int		i;
	char	**tmp;
	int		len; 
	
	len = 0;
	while ((*env)[len])
		len++;
	tmp = (char **)malloc(sizeof(char *) * len + sizeof(char *) * 2);
	if (!tmp)
		return (EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		tmp[i] = ft_strdup((*env)[i]);
		i++;
	}
	tmp[len] = ft_strdup(cmd);
	tmp[len + 1] = NULL;
	i = 0;
	free(*env);
	(*env) = tmp;
	sort_env(env);
	return (EXIT_SUCCESS);
}