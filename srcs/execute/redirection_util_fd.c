/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 20:27:51 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/27 20:28:58 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	read_heredoc(t_cmd *cmd_list, char *str, int i)
{
	if (str == NULL)
		return (EXIT_FAILURE);
	if (ft_strncmp(str, cmd_list->cmdline[i + 1].cmd,
			ft_strlen(cmd_list->cmdline[i + 1].cmd)) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	set_dup2(int in, int out)
{
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
}

void	set_stdin(int fd)
{
	dup2(fd, STDIN_FILENO);
	close(fd);
}
