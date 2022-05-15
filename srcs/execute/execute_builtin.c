/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:07:33 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/14 23:32:42 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);	
}

int		exec_builtin(t_cmd *cmd_list, char ***env)
{
	if (ft_strncmp(cmd_list->cmdline[0].cmd, "cd", 3) == 0)
		return (ft_cd(cmd_list, env));
	else if (ft_strncmp(cmd_list->cmdline[0].cmd, "pwd", 4) == 0)
		return (ft_pwd(cmd_list));
	else if (ft_strncmp(cmd_list->cmdline[0].cmd, "echo", 5) == 0)
		return (ft_echo(cmd_list));
	else if (ft_strncmp(cmd_list->cmdline[0].cmd, "env", 4) == 0)
		return (ft_env(*env));
	else if (ft_strncmp(cmd_list->cmdline[0].cmd, "export", 7) == 0)
		return (ft_export(cmd_list, env));
	else if (ft_strncmp(cmd_list->cmdline[0].cmd, "unset", 6) == 0)
		return (ft_unset(cmd_list, env));
	else if (ft_strncmp(cmd_list->cmdline[0].cmd, "exit", 5) == 0)
		return (ft_exit(cmd_list));
	return (EXIT_FAILURE);	
}
