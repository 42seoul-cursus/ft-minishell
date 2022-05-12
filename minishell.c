/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonghwl <jeonghwl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:56:13 by jeonghwl          #+#    #+#             */
/*   Updated: 2022/05/11 15:06:34 by jeonghwl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

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
		free(tmp->err_manage.errtoken);
		free(tmp);
	}
	i = 0;
	while (command_list->cmdline[i].cmd != NULL)
		free(command_list->cmdline[i++].cmd);
	free(command_list->cmdline);
	free(command_list->err_manage.errtoken);
	free(command_list);
}

void	ft_minishell(char *command, t_cmd **command_list, \
char **copied_env, char *argv[])
{
	add_history(command);
	ft_parse(command_list, command, copied_env);
	g_exit_status = exec(*command_list, argv, &copied_env);
	ft_free_list(*command_list);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*command;
	t_cmd	*command_list;
	char	**copied_env;
	char	*location;

	argc = 1;
	ft_print_title();
	copied_env = ft_init_env(envp);
	ft_signal();
	location = ft_init_location_and_dup2();
	while (1)
	{
		command = readline(location);
		if (!command)
		{
			ft_putstr_fd("exit\n", STDOUT);
			return (0);
		}
		if (*command != '\0' && !is_whitespace(command))
			ft_minishell(command, &command_list, copied_env, argv);
		free(command);
	}
	return (0);
}
