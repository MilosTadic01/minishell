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

// void	ft_pwd(t_data *data)
// {
// 	char	*buff;

// 	buff = malloc(sizeof(char) * PATH_MAX);
// 	data->env->pwd = getcwd(buff, PATH_MAX);
// 	if (data->env->pwd == NULL)
// 	{
// 		strerror(errno);
// 		return ;
// 	}
// 	ft_printf("%s\n", b

char	*ft_getcwd(void)
{
	char	buff[PATH_MAX];
	char	*pwd;

	pwd = getcwd(buff, PATH_MAX);
	if (pwd == NULL)
		perror("minishell: getcwd: ");
	return (pwd);
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = ft_getcwd();
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
}
