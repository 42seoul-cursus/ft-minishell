/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:51:56 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/22 21:38:48 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipe(t_cmd *cmd_list)
{
	close(cmd_list->pip[0]);
	close(cmd_list->pip[1]);
}

void	print_execute_error(char *cmd, int error_code)
{
	ft_putstr_fd(cmd, STDERR);
	ft_putendl_fd(": command not found", STDERR);
	exit(error_code);
}