/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonghwl <jeonghwl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:55:20 by jeonghwl          #+#    #+#             */
/*   Updated: 2022/05/11 13:55:23 by jeonghwl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_free_tokens_box(t_token *tokens_box, int len)
{
	int	i;

	i = 0;
	while (i < len)
		free(tokens_box[i++].cmd);
	return (NULL);
}

int	ft_tokens_len(char const *command, int i, char c)
{
	int		next_index;
	char	*token;

	next_index = 0;
	while (command[next_index])
	{
		if (command[next_index] == c)
			next_index++;
		else
		{
			token = ft_get_token(&next_index, command, c);
			free(token);
			i++;
		}
	}
	return (i);
}

t_token	*ft_assign_tokens_box(t_token *tokens_box, \
char const *command, char c, int i)
{
	int	next_index;

	next_index = 0;
	while (command[next_index])
	{
		if (command[next_index] == c)
			next_index++;
		else
		{
			tokens_box[i].cmd = ft_get_token(&next_index, command, c);
			tokens_box[i].redir_flag = 0;
			if (tokens_box[i].cmd == NULL)
			{
				return (ft_free_tokens_box(tokens_box, i));
			}
			i++;
		}
	}
	tokens_box[i].cmd = 0;
	return (tokens_box);
}

t_token	*ft_command_split(char const *command, char c)
{
	int		i;
	t_token	*tokens_box;

	if (command == NULL)
		return (NULL);
	i = 0;
	tokens_box = (t_token *)malloc(sizeof(t_token) * \
	(ft_tokens_len(command, i, c) + 1));
	i = 0;
	if (tokens_box == NULL)
		return (NULL);
	tokens_box = ft_assign_tokens_box(tokens_box, command, c, i);
	return (tokens_box);
}
