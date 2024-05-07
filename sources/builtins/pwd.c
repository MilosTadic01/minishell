/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:20:03 by mitadic           #+#    #+#             */
/*   Updated: 2024/04/16 17:44:37 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getcwd(void)
{
	char	*buff;
	char	*pwd;

	buff = malloc(PATH_MAX * sizeof(char));
	pwd = getcwd(buff, PATH_MAX);
	g_exit = errno;
	if (pwd == NULL)
		perror("minishell: getcwd: ");
	return (pwd);
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = ft_getcwd();
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
	return (g_exit);
}
