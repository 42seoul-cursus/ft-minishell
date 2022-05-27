/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:17:21 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/27 16:51:52 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_cmd_without_ridir(t_cmd *cmd_list, int non_redir_count)
{
	t_token	*tmp;
	int		i;
	int		len;

	tmp = (t_token *)malloc(sizeof(t_token) * (non_redir_count + 3));
	i = 0;
	len = 0;
	while (cmd_list->cmdline[i].cmd)
	{
		if (!cmd_list->cmdline[i].redir_flag)
		{
			tmp[len].cmd = ft_strdup(cmd_list->cmdline[i].cmd);
			tmp[len++].redir_flag = 0;
		}
		i++;
	}
	tmp[len].cmd = NULL;
	tmp[len].redir_flag = 0;
	free(cmd_list->cmdline);
	cmd_list->cmdline = tmp;
	return (EXIT_SUCCESS);
}

int	check_redirection(t_cmd *cmd_list, int in, int out)
{
	int	i;
	int	non_redir_count;

	non_redir_count = 0;
	i = 0;
	while (cmd_list->cmdline[i].cmd)
	{
		if (cmd_list->cmdline[i].redir_flag)
		{
			if (cmd_list->cmdline[i + 1].cmd == NULL
				|| cmd_list->cmdline[i + 1].redir_flag)
				return (print_syntax_error());
			else
			{
				if (set_redirection(cmd_list, i, in, out))
					return (EXIT_FAILURE);
				i++;
			}
		}
		else
			non_redir_count++;
		i++;
	}
	parse_cmd_without_ridir(cmd_list, non_redir_count);
	return (EXIT_SUCCESS);
}

int	check_syntax(t_cmd *cmd_list)
{
	int	i;

	i = 0;
	while (cmd_list->cmdline[i].cmd)
	{
		if (cmd_list->cmdline[i].redir_flag < 0)
		{
			print_syntax_error();
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	pre_check(t_cmd *cmd_list, char ***env, int stdin_dup, int stdout_dup)
{
	int	error;

	if (check_pipe_syntax(cmd_list))
	{
		set_error_status(env, 1);
		return (EXIT_FAILURE);
	}
	if (check_syntax(cmd_list))
	{
		set_error_status(env, 258);
		return (EXIT_FAILURE);
	}
	if (check_redirection(cmd_list, stdin_dup, stdout_dup))
	{
		set_error_status(env, 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	print_syntax_error(void)
{
	ft_putendl_fd("Syntax Error", STDERR);
	return (EXIT_FAILURE);
}
