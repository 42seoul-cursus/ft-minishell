/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:31:10 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/22 19:32:16 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_newline(char *cmd)
{
	int	len;
	int	i;

	i = 1;
	len = ft_strlen(cmd);
	if (len < 1)
		return (1);
	if (cmd[0] != '-')
		return (1);
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	print_echo(t_cmd *cmd_list)
{
	int		i;
	char	*cmd;

	i = 1;
	while (cmd_list->cmdline[i].cmd)
	{
		cmd = cmd_list->cmdline[i].cmd;
		ft_putstr_fd(cmd, STDOUT);
		if (cmd_list->cmdline[i + 1].cmd)
			ft_putstr_fd(" ", STDOUT);
		i++;
	}
}

void	print_echo_no_newline(t_cmd *cmd_list)
{
	int		i;
	char	*cmd;

	i = 2;
	while (cmd_list->cmdline[i].cmd)
	{
		cmd = cmd_list->cmdline[i].cmd;
		ft_putstr_fd(cmd, STDOUT);
		if (cmd_list->cmdline[i + 1].cmd)
			ft_putstr_fd(" ", STDOUT);
		i++;
	}
}

int	ft_echo(t_cmd *cmd_list)
{
	int		newline_flag;

	if (get_cmd_size(cmd_list) == 1)
	{
		ft_putstr_fd("\n", STDOUT);
		return (EXIT_SUCCESS);
	}
	newline_flag = check_newline(cmd_list->cmdline[1].cmd);
	if (newline_flag)
	{
		print_echo(cmd_list);
		ft_putstr_fd("\n", STDOUT);
	}
	else
		print_echo_no_newline(cmd_list);
	return (EXIT_SUCCESS);
}
