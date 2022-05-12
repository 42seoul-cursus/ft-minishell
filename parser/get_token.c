/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonghwl <jeonghwl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:55:43 by jeonghwl          #+#    #+#             */
/*   Updated: 2022/05/11 13:55:45 by jeonghwl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_quote_close_open(char const *command, int *quote)
{
	if (*command == '"' && (*quote) == '"')
		(*quote) = CLOSE;
	else if (*command == '"' && (*quote) == CLOSE)
		(*quote) = '"';
	else if (*command == '\'' && (*quote) == '\'')
		(*quote) = CLOSE;
	else if (*command == '\'' && (*quote) == CLOSE)
		(*quote) = '\'';
}

int	ft_redi_count_as_token(char const **command, int *count)
{
	while (**command)
	{
		if ((**command) == '>' || (**command) == '<')
			(*count)++;
		else
			return (*count);
		(*command)++;
	}
	return (*count);
}

int	ft_token_count(char const *command, const char c, int *count, \
	t_token_quote_status *t_q)
{
	if (t_q->token_index == 0)
	{
		if (*command != c)
		{
			t_q->token_index = 1;
			(*count)++;
		}
	}
	else
	{
		if (*command == c && t_q->quote == CLOSE)
			return (BREAK);
		else if ((*command == '>' || *command == '<') && t_q->quote == CLOSE)
			return (BREAK);
		else
			(*count)++;
	}
	return (CONTINUE);
}

static int	ft_token_len(char const *command, const char c)
{
	int						count;
	t_token_quote_status	t_q;

	count = 0;
	t_q.token_index = 0;
	t_q.quote = CLOSE;
	if (ft_redi_count_as_token(&command, &count) != 0)
		return (count);
	while (*command)
	{
		ft_quote_close_open(command, &t_q.quote);
		if (ft_token_count(command, c, &count, &t_q) == BREAK)
			break ;
		command++;
	}
	return (count);
}

char	*ft_get_token(int *next_index, char const *command, const char c)
{
	int		token_len;
	char	*token_box;
	int		i;

	token_len = ft_token_len(&command[*next_index], c);
	token_box = (char *)malloc(sizeof(char) + (token_len + 1));
	if (token_box == NULL)
		return (NULL);
	i = -1;
	while (++i < token_len)
		token_box[i] = command[*next_index + i];
	token_box[i] = '\0';
	*next_index += token_len;
	return (token_box);
}
