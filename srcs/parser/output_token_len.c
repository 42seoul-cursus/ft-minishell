/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_token_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonghwl <jeonghwl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:55:51 by jeonghwl          #+#    #+#             */
/*   Updated: 2022/05/24 20:49:59 by jeonghwl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_closed_quote(char *token, char quote)
{
	int	index;

	index = 1;
	while (token[index] && token[index] != quote)
		index++;
	if (token[index] == '\0')
		return (UNCLOSED);
	return (CLOSED);
}

int	ft_env_cnt(char *token, int *count, char **envp)
{
	int		key_len;
	char	*status;

	key_len = 0;
	if (token[1] == '?')
	{
		status = ft_env_value("ERROR_STATUS", envp);
		if (!status)
			status = "0";
		*count += ft_strlen(status);
		return (1);
	}
	if (token[1] == '\0' || token[1] == '\"')
	{
		*count += 1;
		return (0);
	}
	key_len = ft_env_key_len(token);
	*count += ft_env_value_len(token, key_len, envp);
	return (key_len);
}

int	ft_quote_cnt(char *token, int *count, char **envp, char q)
{
	int	index;

	index = 1;
	if (q == '\"')
	{
		while (token[index] && (token[index] != '\"'))
		{
			if (token[index] == '$')
				index += (ft_env_cnt(&token[index], count, envp) + 1);
			else
			{
				index++;
				(*count)++;
			}
		}
	}
	else if (q == '\'')
	{
		while (token[index] && (token[index] != '\''))
		{
			index++;
			(*count)++;
		}
	}
	return (index);
}

int	ft_output_token_len(char *token, char **envp)
{
	int	index;
	int	count;

	count = 0;
	index = -1;
	while (token[++index])
	{
		if (token[index] == '\'' && \
			ft_is_closed_quote(&token[index], '\'') == CLOSED)
			index += ft_quote_cnt(&token[index], &count, envp, '\'');
		else if (token[index] == '\"' && \
			ft_is_closed_quote(&token[index], '\"') == CLOSED)
			index += ft_quote_cnt(&token[index], &count, envp, '\"');
		else if (token[index] == '$')
			index += ft_env_cnt(&token[index], &count, envp);
		else if (token[index])
			count++;
	}
	return (count);
}
