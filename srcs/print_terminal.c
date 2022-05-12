/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonghwl <jeonghwl@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:07:40 by jeonghwl          #+#    #+#             */
/*   Updated: 2022/05/11 14:58:27 by jeonghwl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_title(void)
{
	char	*username;

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

char	*ft_init_location_and_dup2(void)
{
	char	*location;
	char	*dir;
	char	*user;

	dup2(STDIN, 100);
	dup2(STDOUT, 101);
	user = getenv("USER");
	location = ft_strdup("\033[33;35m");
	if (!user)
		location = ft_strjoin_location(location, "tester");
	else
		location = ft_strjoin_location(location, user);
	location = ft_strjoin_location(location, "\033[33;37m:");
	dir = getcwd(0, 0);
	location = ft_strjoin_location(location, "\033[33;36m");
	location = ft_strjoin_location(location, dir);
	location = ft_strjoin_location(location, "\033[33;37m $ ");
	free(dir);
	return (location);
}
