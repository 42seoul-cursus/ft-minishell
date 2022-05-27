/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_out_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonghwl <jeonghwl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 08:35:14 by jeonghwl          #+#    #+#             */
/*   Updated: 2022/05/11 13:37:56 by jeonghwl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_assign_env(char *in_tok, char **out_token, char **envp)
{
	int		in_tok_idx;
	char	*key;
	char	*env_val;
	int		env_len;

	in_tok_idx = 0;
	if (ft_if_question(in_tok, &out_token, envp) == 1)
		return (1);
	if (ft_if_null_or_d_quote(in_tok, &out_token) == 0)
		return (0);
	in_tok_idx = ft_env_key(in_tok, &key);
	env_val = ft_env_value(key, envp);
	env_len = ft_strlen(env_val);
	ft_memcpy(*out_token, env_val, env_len);
	*out_token += env_len;
	free(key);
	return (in_tok_idx);
}

void	*ft_out_tok_assign_cnt(char **out_tok, char *in_tok, int *in_tok_idx)
{
	**out_tok = in_tok[*in_tok_idx];
	(*out_tok)++;
	(*in_tok_idx)++;
	return (0);
}

int	ft_quote_assign_and_cnt(char *in_tok, char **out_tok, char **envp, char q)
{
	int	in_tok_idx;

	in_tok_idx = 1;
	if (q == '\"')
	{
		while (in_tok[in_tok_idx] && in_tok[in_tok_idx] != '\"')
		{
			if (in_tok[in_tok_idx] == '$')
				in_tok_idx += (ft_assign_env(&in_tok[in_tok_idx], \
				out_tok, envp) + 1);
			else
				ft_out_tok_assign_cnt(out_tok, in_tok, &in_tok_idx);
		}
	}
	else if (q == '\'')
	{
		while (in_tok[in_tok_idx] && in_tok[in_tok_idx] != '\'')
			ft_out_tok_assign_cnt(out_tok, in_tok, &in_tok_idx);
	}
	return (in_tok_idx);
}

void	*ft_assign_output_token(char *in_tok, char *out_tok, char **ev)
{
	int		i;
	char	*out_tok_tmp;

	i = -1;
	out_tok_tmp = out_tok;
	while (in_tok[++i])
	{
		if (in_tok[i] == '\'' && \
			ft_is_closed_quote(&in_tok[i], '\'') == CLOSED)
			i += ft_quote_assign_and_cnt(&in_tok[i], &out_tok_tmp, ev, '\'');
		else if (in_tok[i] == '\"' && \
			ft_is_closed_quote(&in_tok[i], '\"') == CLOSED)
			i += ft_quote_assign_and_cnt(&in_tok[i], &out_tok_tmp, ev, '\"');
		else if (in_tok[i] == '$')
			i += ft_assign_env(&in_tok[i], &out_tok_tmp, ev);
		else if (in_tok[i])
		{
			*out_tok_tmp = in_tok[i];
			out_tok_tmp++;
		}
	}
	*out_tok_tmp = '\0';
	return (0);
}
