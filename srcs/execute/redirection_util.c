/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:17:21 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/20 11:33:23 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

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

int	check_redirection(t_cmd *cmd_list)
{
	int	i;
	int	non_redir_count;

	non_redir_count = 0;
	i = 0;
	while (cmd_list->cmdline[i].cmd)
	{
		if (cmd_list->cmdline[i].redir_flag)
		{
			if (cmd_list->cmdline[i + 1].cmd == NULL || cmd_list->cmdline[i + 1].redir_flag)
				return (print_syntax_error());
			else
			{
				set_redirection(cmd_list->cmdline, i);
				i++;
			}
		}
		else
			non_redir_count++;
		i++;
	}
	
	parse_cmd_without_ridir(cmd_list, non_redir_count);
	i = 0;
	return (EXIT_SUCCESS);
}

int	pre_check(t_cmd *cmd_list)
{
	if (check_redirection(cmd_list))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	print_syntax_error()
{
	ft_putendl_fd("Syntax Error", STDERR);
}