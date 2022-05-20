/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:13:05 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/19 23:23:02 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	redirection_out(t_token *cmdline, int i)
{
	int	fd;

	fd = open(cmdline[i + 1].cmd, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	cmdline[i + 1].redir_flag = 1;
	return (EXIT_SUCCESS);
}

int	redirection_in(t_token *cmdline, int i)
{
	int	fd;

	fd = open(cmdline[i + 1].cmd, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	cmdline[i + 1].redir_flag = 1;
	return (EXIT_SUCCESS);
}

int	redirection_out_append(t_token *cmdline, int i)
{
	int	fd;

	fd = open(cmdline[i + 1].cmd, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	cmdline[i + 1].redir_flag = 1;
	return (EXIT_SUCCESS);
}


int	redirection_heredoc(t_token *cmdline, int i)
{
	int		fd;
	int		*str;

	fd = open(HEREDOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		str = readline("> ");
		if (str)
			if (ft_strncmp(str, cmdline[i + 1].cmd, ft_strlen(cmdline[i + 1].cmd)) == 0)
				break;
		ft_putendl_fd(str, fd);
		free(str);
	}
	close(fd);
	fd = open(HEREDOC, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	cmdline[i + 1].redir_flag = 1;
	return (EXIT_SUCCESS);
}

int	set_redirection(t_token *cmdline, int i)
{
	if (ft_strlen(cmdline[i].cmd) > 2)
		return (EXIT_FAILURE);
	if (ft_strncmp(cmdline[i].cmd, ">", 2) == 0)
		return (redirection_out(cmdline, i));
	else if (ft_strncmp(cmdline[i].cmd, "<<", 3) == 0)
		return (redirection_heredoc(cmdline, i));
	else if (ft_strncmp(cmdline[i].cmd, ">>", 3) == 0)
		return (redirection_out_append(cmdline, i));
	else if (ft_strncmp(cmdline[i].cmd, "<", 2) == 0)
		return (redirection_in(cmdline, i));
}