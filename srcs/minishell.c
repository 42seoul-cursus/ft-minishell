/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonghwl <jeonghwl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:56:13 by jeonghwl          #+#    #+#             */
/*   Updated: 2022/05/27 19:59:32 by jeonghwl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_whitespace(char *commands)
{
	int	i;

	i = 0;
	while (commands[i] != '\0')
	{
		if (commands[i] != 32 && !(commands[i] >= 9 && commands[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}

void	ft_free_list(t_cmd *command_list)
{
	t_cmd	*tmp;
	int		i;

	while (command_list->next != NULL)
	{
		i = 0;
		tmp = command_list;
		command_list = command_list->next;
		while (tmp->cmdline[i].cmd != NULL)
			free(tmp->cmdline[i++].cmd);
		free(tmp->cmdline);
		free(tmp);
	}
	i = 0;
	while (command_list->cmdline[i].cmd != NULL)
		free(command_list->cmdline[i++].cmd);
	free(command_list->cmdline);
	free(command_list);
}

void	ft_minishell(char *command, t_cmd **command_list, \
char ***copied_env, char *argv[])
{
	(void)*argv;
	add_history(command);
	ft_parse(command_list, command, *copied_env);
	execute(*command_list, copied_env);
	ft_free_list(*command_list);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*command;
	t_cmd	*command_list;
	char	**copied_env;
	char	*location;

	ft_print_title(argc);
	copied_env = ft_init_env(envp);
	ft_signal();
	init_env(&copied_env);
	while (1)
	{
		location = ft_init_location();
		command = readline(location);
		if (!command)
		{
			ft_putstr_fd("\x1b[1A", STDOUT);
			ft_putstr_fd(location, STDOUT);
			ft_putstr_fd("exit\n", STDOUT);
			return (0);
		}
		if (*command != '\0' && !is_whitespace(command))
			ft_minishell(command, &command_list, &copied_env, argv);
		free(command);
	}
	return (0);
}
