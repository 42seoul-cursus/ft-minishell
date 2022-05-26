/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:53:42 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/25 20:23:35 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i], STDOUT);
		i++;
	}
	return (0);
}

void	sort_env(char ***env)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	len = 0;
	while ((*env)[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1)
		{
			if (ft_strncmp((*env)[j], (*env)[j + 1], ft_strlen((*env)[j])) > 0)
			{
				tmp = (*env)[j];
				(*env)[j] = (*env)[j + 1];
				(*env)[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
