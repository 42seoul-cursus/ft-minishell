/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 08:16:29 by jeonghwl          #+#    #+#             */
/*   Updated: 2022/05/27 21:41:09 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_init_t_cmd(t_cmd *result, int pipe_status, int start_index)
{
	(void)start_index;
	result->path = NULL;
	result->pipe_flag = pipe_status;
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
