/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:49:13 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/17 21:51:42 by hkim2            ###   ########.fr       */
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
