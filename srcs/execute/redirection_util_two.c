/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util_two.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:49:00 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/24 19:52:43 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incldes/minishell.h"


void	check_prev_pipe(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	tmp = cmd_list;
	while (tmp->next)
	{
		if (tmp->right_flag)
			tmp->next->prev_pipe_flag = 1;
		else
			tmp->next->prev_pipe_flag = 0;
		tmp = tmp->next;
	}
}

void	pre_init(t_cmd *cmd_list)
{
	t_cmd	*tmp;
	
	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->cmdline[0].cmd == NULL)
			return ;
		tmp->redir_flag = 0;
		tmp->right_flag = 0;
		tmp->prev_pipe_flag = 0;
		tmp = tmp->next;
	}
}

int	check_pipe_syntax(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->cmdline[0].cmd == NULL)
			return (print_syntax_error());
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}