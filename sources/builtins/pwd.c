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

#include <errno.h>

void	ft_pwd(t_data *data)
{
	char	*buff;

	buff = malloc(sizeof(char) * PATH_MAX);
	data->env->pwd = getcwd(buff, PATH_MAX);
	if (data->env->pwd == NULL)
		strerror(errno);
	ft_printf("%s\n", buff);
}

