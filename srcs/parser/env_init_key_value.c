/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_key_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonghwl <jeonghwl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:55:36 by jeonghwl          #+#    #+#             */
/*   Updated: 2022/05/11 13:55:37 by jeonghwl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_init_env(char **envs)
{
	char	**box;
	int		i;

	i = 0;
	while (envs[i])
		i++;
	box = malloc(sizeof(char *) * (i + 1));
	if (!box)
		return (NULL);
	i = -1;
	while (envs[++i])
		box[i] = ft_strdup(envs[i]);
	box[i] = NULL;
	return (box);
}

int	ft_env_key_len(char *token)
{
	int	i;

	i = 0;
	if (ft_isdigit(token[1]))
		return (1);
	while (token[++i])
	{
		if (!(ft_isalnum(token[i]) || token[i] == '_'))
			return (i - 1);
	}
	return (i - 1);
}

int	ft_env_key(char *src, char **key)
{
	int	key_len;

	key_len = ft_env_key_len(src);
	*key = ft_substr(src, 1, key_len);
	return (key_len);
}

char	*ft_env_value(char *key, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if ((!ft_strncmp(key, envp[i], ft_strlen(key))) \
		&& envp[i][ft_strlen(key)] == '=')
			return (envp[i] + ft_strlen(key) + 1);
	}
	return ("");
}

int	ft_env_value_len(char *token, int key_len, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if ((!ft_strncmp(&token[1], envp[i], key_len)) \
		&& envp[i][key_len] == '=')
		{
			return (ft_strlen(envp[i] + key_len + 1));
		}
	}
	return (0);
}
