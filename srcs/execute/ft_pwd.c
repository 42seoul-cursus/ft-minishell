/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:19:28 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/12 18:24:58 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_pwd(t_cmd *cmd_list)
{
	char	buf[1024];
	
	
	if (get_cmd_size(cmd_list) > 1 && !is_redirection(cmd_list->cmdline[1].cmd) )
	{
		printf("pwd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	if (getcwd(buf, 1024))
	{
		printf("%s\n", buf);
		return (EXIT_SUCCESS);
	}
	else
		printf("getcwd fail\n");
	return (EXIT_FAILURE);
}