/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:49:13 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/25 20:21:11 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**bind_cmd(t_token *cmdline)
{
	int		i;
	int		len;
	char	**cmd_arg;

	len = 0;
	while (cmdline[len].cmd)
		len++;
	cmd_arg = (char **)malloc(sizeof(char *) * (len + 1));
	if (!cmd_arg)
		return (NULL);
	i = -1;
	while (cmdline[++i].cmd)
		cmd_arg[i] = ft_strdup(cmdline[i].cmd);
	cmd_arg[i] = NULL;
	return (cmd_arg);
}

int	is_redirection(char *cmd)
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

void	exec_pipe(t_cmd *cmd_list, char ***env)
{
	if (is_builtin(cmd_list->cmdline[0].cmd))
		execute_builtin_pipe(cmd_list, env);
	else
		execute_cmd_pipe(cmd_list, env);
}

void	exec_without_pipe(t_cmd *cmd_list, char ***env, int in_dup, int out_dup)
{
	if (is_builtin(cmd_list->cmdline[0].cmd))
		execute_builtin(cmd_list, env, in_dup, out_dup);
	else
		execute_cmd(cmd_list, env, in_dup, out_dup);
}
