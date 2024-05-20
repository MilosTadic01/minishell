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

char	*ft_getcwd(t_exe *b)
{
	char	*buff;
	char	*pwd;

	buff = NULL;
	pwd = NULL;
	buff = malloc(PATH_MAX * sizeof(char));
	if (!buff)
		ft_putstr_fd("minishell: pwd: malloc fail\n", STDERR_FILENO);
	else
	{
		pwd = getcwd(buff, PATH_MAX);
		b->exit_st = errno;
		if (pwd == NULL)
			perror("minishell: getcwd: ");
	}
	return (pwd);
}

int	ft_pwd(t_exe *b)
{
	char	*pwd;

	pwd = ft_getcwd(b);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	if (pwd)
		free(pwd);
	return (b->exit_st);
}
