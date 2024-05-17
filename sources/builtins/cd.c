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

static int	too_many_args(int size)
{
	if (size > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

static int	try_to_go_home_if_no_args(int size, t_list **env)
{
	if (size > 1)
		return (0);
	if (ft_getenv("HOME", *env) == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (-1);
	}
	else if (chdir(ft_getenv("HOME", *env)) < 0)
		perror("minishell: cd: ");
	g_exit = errno;
	return (g_exit);
}

/*envvar HOME isn't what Bash accesses for cd ~*/
static int	try_to_go_to_path(int size, char **cmdarr, t_list **env)
{
	(void)env;
	if (size < 2)
		return (0);
	if (ft_strcmp(cmdarr[1], "~") == 0)
	{
		ft_putstr_fd("minishell: cd: ~home (!envvar HOME) not specified\n", 2);
		return (1);
	}
	if (chdir(cmdarr[1]) < 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(cmdarr[1]);
	}
	g_exit = errno;
	return (g_exit);
}

int	ft_cd(int size, char **cmdarr, t_list **env)
{
	char	*newpwd;
	char	*cwd;

	if (!cmdarr && !(*cmdarr))
		return (1);
	if (too_many_args(size))
		return (1);
	if (try_to_go_home_if_no_args(size, env) != SUCCESS)
		return (1);
	if (try_to_go_to_path(size, cmdarr, env) != SUCCESS)
		return (1);
	cwd = ft_getcwd();
	newpwd = ft_strjoin("PWD=", cwd);
	ft_export(newpwd, env);
	free(cwd);
	free(newpwd);
	return (SUCCESS);
}
