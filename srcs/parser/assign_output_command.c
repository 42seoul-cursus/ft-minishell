/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_output_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonghwl <jeonghwl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:55:02 by jeonghwl          #+#    #+#             */
/*   Updated: 2022/05/27 19:41:00 by jeonghwl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_redir_chk(char *str)
{
	size_t	str_len;

	str_len = ft_strlen(str);
	if (!ft_strncmp("<<", str, str_len) || \
			!ft_strncmp(">>", str, str_len) || \
			!ft_strncmp("<", str, str_len) || \
			!ft_strncmp(">", str, str_len))
		return (1);
	else
		return (0);
}

int	ft_if_question(char *input_token, char ***output_token, char **envp)
{
	char	*status;

	if (input_token[1] == '?')
	{
		status = ft_env_value("ERROR_STATUS", envp);
		if (!status)
			status = "0";
		ft_memcpy(**output_token, status, ft_strlen(status));
		**output_token += ft_strlen(status);
		return (1);
	}
	return (0);
}

int	ft_if_null_or_d_quote(char *input_token, char ***output_token)
{
	if (input_token[1] == '\0' || input_token[1] == '\"')
	{
		(***output_token) = '$';
		(**output_token) += 1;
		return (0);
	}
	return (1);
}

void	ft_if_redir_in_token(t_token *token)
{
	if ((*token).cmd[0] == '<' || (*token).cmd[0] == '>')
	{
		if (ft_redir_chk((*token).cmd))
			(*token).redir_flag = 1;
		else
			(*token).redir_flag = -1;
	}
}

t_token	*ft_assign_output_command(t_token *tokens, char **envp)
{
	size_t	i;
	char	*tmp_token;
	int		output_token_len;

	i = 0;
	while (tokens[i].cmd)
	{
		output_token_len = 0;
		tmp_token = tokens[i].cmd;
		output_token_len = ft_output_token_len(tmp_token, envp);
		ft_if_redir_in_token(&tokens[i]);
		tokens[i].cmd = (char *)malloc(sizeof(char) * (output_token_len + 1));
		ft_assign_output_token(tmp_token, tokens[i].cmd, envp);
		free(tmp_token);
		i++;
	}
	return (tokens);
}
