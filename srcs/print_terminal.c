/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonghwl <jeonghwl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:07:40 by jeonghwl          #+#    #+#             */
/*   Updated: 2022/05/25 13:41:03 by jeonghwl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_title(int argc)
{
	char	*username;

	(void)argc;
	username = getenv("USER");
	printf("\e[2J\e[H\e[33;33m-----------------------------------------");
	printf("\e[33;33m--------------------------\e[0m\n");
	printf("\e[33m███╗   ███╗██╗███╗   ██╗██╗");
	printf("███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝");
	printf("██║  ██║██╔════╝██║     ██║     \n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗");
	printf("███████║█████╗  ██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║");
	printf("██╔══██║██╔══╝  ██║     ██║     \n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║");
	printf("██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝");
	printf("╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\e[0m\n");
	printf("\e[33;33m-----------------------------------------");
	printf("\e[33;33m--------------------------\e[0m\n");
	printf("\n\e[33;32m                          Welcome %s\e[0m\n\n", username);
}

char	*ft_strjoin_location(char *s1, char const *s2)
{
	char	*box;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	box = (char *)malloc(sizeof(*box) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (box == 0)
		return (NULL);
	while (s1[i])
	{
		box[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		box[i] = s2[j];
		j++;
		i++;
	}
	box[i] = '\0';
	free(s1);
	return (box);
}

char	*ft_init_location(void)
{
	char	*location;
	char	*dir;
	char	*user;

	user = getenv("USER");
	if (!user)
		location = ft_strdup("tester");
	else
		location = ft_strdup(user);
	location = ft_strjoin_location(location, ":");
	dir = getcwd(0, 0);
	location = ft_strjoin_location(location, dir);
	location = ft_strjoin_location(location, " $ ");
	free(dir);
	return (location);
}
