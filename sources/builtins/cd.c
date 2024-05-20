/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:03:34 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/20 17:43:51 by mitadic          ###   ########.fr       */
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

static int	try_to_go_home_if_no_args(int size, t_exe *b)
{
	if (size > 1)
		return (0);
	if (ft_getenv("HOME", *(b->env)) == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (-1);
	}
	else if (chdir(ft_getenv("HOME", *(b->env))) < 0)
		perror("minishell: cd: ");
	b->exit_st = errno;
	return (b->exit_st);
}

/*envvar HOME isn't what Bash accesses for cd ~*/
static int	try_to_go_to_path(int size, char **cmdarr, t_exe *b)
{
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
	b->exit_st = errno;
	return (b->exit_st);
}

int	ft_cd(int size, char **cmdarr, t_exe *b)
{
	char	*newpwd;
	char	*cwd;

	if (!cmdarr && !(*cmdarr))
		return (1);
	if (too_many_args(size))
		return (1);
	if (try_to_go_home_if_no_args(size, b) != SUCCESS)
		return (1);
	if (try_to_go_to_path(size, cmdarr, b) != SUCCESS)
		return (1);
	cwd = ft_getcwd(b);
	newpwd = ft_strjoin("PWD=", cwd);
	ft_export(newpwd, b->env);
	free(cwd);
	free(newpwd);
	return (SUCCESS);
}
