/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:57:51 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/25 20:24:26 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_numeric(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

void	print_exit_numeric(char *cmd)
{
	ft_putendl_fd("exit", STDERR);
	ft_putstr_fd("bash: exit: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putendl_fd(": numeric argument required", STDERR);
}

void	print_exit_many_arg(void)
{
	ft_putendl_fd("exit", STDERR);
	ft_putendl_fd("bash: exit: too many arguments", STDERR);
}

int	execute_exit(t_cmd *cmd_list)
{
	int	num;

	if (!is_numeric(cmd_list->cmdline[1].cmd))
	{
		print_exit_numeric(cmd_list->cmdline[1].cmd);
		exit(255);
	}
	else if (get_cmd_size(cmd_list) > 2)
	{
		print_exit_many_arg();
		return (EXIT_FAILURE);
	}
	ft_putendl_fd("exit", STDOUT);
	num = ft_atoi(cmd_list->cmdline[1].cmd, NULL) % 256;
	exit(num);
}

int	ft_exit(t_cmd *cmd_list)
{
	int	is_error;

	is_error = EXIT_SUCCESS;
	if (get_cmd_size(cmd_list) == 1)
	{
		ft_putendl_fd("exit", STDOUT);
		exit(EXIT_SUCCESS);
	}
	is_error = execute_exit(cmd_list);
	return (is_error);
}
