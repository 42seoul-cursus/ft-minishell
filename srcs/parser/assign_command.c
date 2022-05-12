/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonghwl <jeonghwl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 08:16:29 by jeonghwl          #+#    #+#             */
/*   Updated: 2022/05/11 15:32:54 by jeonghwl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_init_t_cmd(t_cmd *result, int pipe_status, int start_index)
{
	result->path = NULL;
	result->pipe_flag = pipe_status;
	if (start_index == 0 && pipe_status == 0)
		result->exit_flag = 1;
	else
		result->exit_flag = 0;
	result->err_manage.errcode = 0;
	result->err_manage.errindex = 0;
	result->err_manage.errtoken = NULL;
	result->next = NULL;
	return (0);
}

t_cmd	*ft_assign_command(char *command, int pipe_status, \
char **envp, int start_index)
{
	t_cmd	*result;

	result = (t_cmd *)malloc(sizeof(t_cmd));
	if (!result)
		return (NULL);
	result->cmdline = ft_command_split(command, ' ');
	ft_assign_output_command(result->cmdline, envp);
	ft_init_t_cmd(result, pipe_status, start_index);
	return (result);
}
