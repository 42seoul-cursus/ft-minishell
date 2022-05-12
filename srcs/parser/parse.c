/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonghwl <jeonghwl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:55:59 by jeonghwl          #+#    #+#             */
/*   Updated: 2022/05/11 15:29:00 by jeonghwl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_if_quote(char *commands, int *command_status, int i)
{
	if ((commands[i] == '\"' || commands[i] == '\'') && \
	command_status[QUOTE] == CLOSE)
		command_status[QUOTE] = OPEN;
	else if ((commands[i] == '\"' || commands[i] == '\'') && \
	command_status[QUOTE] == OPEN)
		command_status[QUOTE] = CLOSE;
}

void	ft_init_parse_data(int *i, int *next_index, int (*command_status)[2])
{
	(*i) = 0;
	(*next_index) = 0;
	(*command_status)[QUOTE] = CLOSE;
	(*command_status)[END] = NO;
}

void	ft_connect_command(t_cmd **command_list, t_cmd **next_t_command, \
t_cmd **tmp, int next_index)
{
	if (next_index == 0)
	{
		*command_list = (*next_t_command);
		(*tmp) = *command_list;
	}
	else
	{
		(*command_list)->next = (*next_t_command);
		*command_list = (*command_list)->next;
	}
}

void	ft_cut_commands(int i, char *commands, int *command_status)
{
	if (commands[i] == '|')
		commands[i] = '\0';
	else
		command_status[END] = YES;
}

void	ft_parse(t_cmd **command_list, char *cmds, char **envp)
{
	int		i;
	int		next_index;
	int		cmd_status[2];
	t_cmd	*tmp;
	t_cmd	*next_t_command;

	ft_init_parse_data(&i, &next_index, &cmd_status);
	while (1)
	{
		ft_if_quote(cmds, cmd_status, i);
		if (cmds[i] == '\0' || (cmds[i] == '|' && (cmd_status[QUOTE]) == CLOSE))
		{
			ft_cut_commands(i, cmds, cmd_status);
			next_t_command = ft_assign_command(&cmds[next_index], \
			cmd_status[END], envp, next_index);
			if ((next_t_command) == 0)
				return ;
			ft_connect_command(command_list, &next_t_command, &tmp, next_index);
			if (cmd_status[END] == YES)
				break ;
			next_index = i + 1;
		}
		i++;
	}
	*command_list = tmp;
}
