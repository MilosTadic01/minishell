/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:03:34 by mitadic           #+#    #+#             */
/*   Updated: 2024/04/20 17:43:51 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *ft_cd_get_fullpath(char *dest)
{
	int		i;

	i = 0;
	while (dest[i++] == '.')
		while (dest[i] == '/')
			i++;
		if (dest[i] == '.' && dest[i - 1] == '.')

			return (ft_strjoin(getcwd(buff, PATH_MAX), dest));
	else if (dest[0] == '/')
		;
}

// Remember to, outside of the ft, check if more args than dest, then print error
// STDIN_FILENO: no. STDOUT_FILENO: no.
void	ft_cd(t_list *env, char *dest)
{
	char	*fullpath;

	if (!dest)
	{
		if (ft_getenv(env, "HOME") == NULL)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		else if (chdir(ft_getenv(env, "HOME")) < 0)
			ft_putstr_fd(strerror(errno), 2);
		return ;
	}
	fullpath = ft_cd_get_fullpath(dest);
	if (chdir(fullpath) < 0)
		ft_putstr_fd(strerror(errno), 2);
}
