/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:57:15 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/27 20:32:24 by hkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_error_status(char ***env, int status)
{
	char		*str;

	str = ft_strjoin("ERROR_STATUS=", ft_itoa(status));
	add_env(str, env);
	free(str);
}

void	set_parent_process_status(t_cmd *cmd_list, char ***env)
{
	close_pipe(cmd_list);
	set_child_process_status(cmd_list, env);
}
