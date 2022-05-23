/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim2 <hkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:57:15 by hkim2             #+#    #+#             */
/*   Updated: 2022/05/23 23:39:39 by hkim2            ###   ########.fr       */
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