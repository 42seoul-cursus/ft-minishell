/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:43:23 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/12 21:40:20 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 
int		is_redirection(char *cmd)
{
	if (ft_strncmp(cmd, ">", 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "<", 1) == 0)
		return (1);
	if (ft_strncmp(cmd, ">>", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "<<", 2) == 0)
		return (1);
	return (0);
}

int	get_cmd_size(t_cmd *cmd_list)
{
	int	i;

	i = 0;

	while (cmd_list->cmdline[i].cmd)
		i++;
	return (i);
}

void	execute(t_cmd *cmd_list, char ***env)
{
	int	i;
	char	**path;

	path = get_cmd_path(*env);
	i = 0;
	while (cmd_list)
	{
		if (cmd_list->pipe_flag)
		{}
		else if (is_builtin(cmd_list->cmdline[i].cmd))
		{
			if (exec_builtin(cmd_list, env))
				return ;
			//printf("build in error\n");
			
		}
		cmd_list = cmd_list->next;
	}	
	return ;
}
