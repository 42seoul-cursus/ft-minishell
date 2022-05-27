/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:13:05 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/27 20:28:09 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirection_out(t_cmd *cmd_list, int i)
{
	int	fd;

	fd = open(cmd_list->cmdline[i + 1].cmd, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (print_file_error(cmd_list->cmdline[i + 1].cmd));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	cmd_list->cmdline[i + 1].redir_flag = 1;
	cmd_list->right_flag = 1;
	return (EXIT_SUCCESS);
}

int	redirection_in(t_cmd *cmd_list, int i)
{
	int	fd;

	fd = open(cmd_list->cmdline[i + 1].cmd, O_RDONLY);
	if (fd == -1)
		return (print_file_error(cmd_list->cmdline[i + 1].cmd));
	dup2(fd, STDIN_FILENO);
	close(fd);
	cmd_list->cmdline[i + 1].redir_flag = 1;
	return (EXIT_SUCCESS);
}

int	redirection_out_append(t_cmd *cmd_list, int i)
{
	int	fd;

	fd = open(cmd_list->cmdline[i + 1].cmd, O_CREAT | O_WRONLY | O_APPEND,
			0644);
	if (fd == -1)
		return (print_file_error(cmd_list->cmdline[i + 1].cmd));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	cmd_list->cmdline[i + 1].redir_flag = 1;
	cmd_list->right_flag = 1;
	return (EXIT_SUCCESS);
}

int	redirection_heredoc(t_cmd *cmd_list, int i, int in, int out)
{
	int		fd;
	char	*str;
	int		tmp_fd;

	tmp_fd = dup(STDOUT_FILENO);
	set_dup2(in, out);
	fd = open(HEREDOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (print_file_error(cmd_list->cmdline[i + 1].cmd));
	while (1)
	{
		str = readline("> ");
		if (!read_heredoc(cmd_list, str, i))
			break ;
		ft_putendl_fd(str, fd);
		free(str);
	}
	close(fd);
	dup2(tmp_fd, STDOUT_FILENO);
	fd = open(HEREDOC, O_RDONLY, 0644);
	if (fd == -1)
		return (print_file_error(cmd_list->cmdline[i + 1].cmd));
	set_stdin(fd);
	cmd_list->cmdline[i + 1].redir_flag = 1;
	return (EXIT_SUCCESS);
}

int	set_redirection(t_cmd *cmd_list, int i, int in, int out)
{
	if (ft_strlen(cmd_list->cmdline[i].cmd) > 2)
		return (EXIT_FAILURE);
	if (ft_strncmp(cmd_list->cmdline[i].cmd, ">", 2) == 0)
		return (redirection_out(cmd_list, i));
	else if (ft_strncmp(cmd_list->cmdline[i].cmd, "<<", 3) == 0)
		return (redirection_heredoc(cmd_list, i, in, out));
	else if (ft_strncmp(cmd_list->cmdline[i].cmd, ">>", 3) == 0)
		return (redirection_out_append(cmd_list, i));
	else if (ft_strncmp(cmd_list->cmdline[i].cmd, "<", 2) == 0)
		return (redirection_in(cmd_list, i));
	return (EXIT_SUCCESS);
}
