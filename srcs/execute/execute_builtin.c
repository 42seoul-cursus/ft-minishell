/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:07:33 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/12 21:28:30 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	return (0);	
}

int		exec_builtin(t_cmd *cmd_list, char ***env)
{
	if (ft_strncmp(cmd_list->cmdline[0].cmd, "cd", 2) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp(cmd_list->cmdline[0].cmd, "pwd", 3) == 0)
		return (ft_pwd(cmd_list));
	else if (ft_strncmp(cmd_list->cmdline[0].cmd, "echo", 4) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp(cmd_list->cmdline[0].cmd, "env", 3) == 0)
		return (ft_env(*env));
	else if (ft_strncmp(cmd_list->cmdline[0].cmd, "export", 6) == 0)
		return (ft_export(cmd_list, env));
	else if (ft_strncmp(cmd_list->cmdline[0].cmd, "unset", 5) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp(cmd_list->cmdline[0].cmd, "exit", 4) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);	
}
