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

static int  too_many_args(char **strarr)
{
    if (strarr[1] && strarr[2])
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        return (1);
    }
    return (0);
}

static int	try_to_go_home_if_no_args(t_list *env, char **cmdarr)
{
	if (cmdarr[1])
		return (1);
	if (ft_getenv(env, "HOME") == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (-1);
	}
	else if (chdir(ft_getenv(env, "HOME")) < 0)
	{
		perror("minishell: cd: ");
		return (-1);
	}
	return (0);
}

static void	try_to_go_to_path(t_list *env, char **cmdarr)
{
	if (ft_strcmp(cmdarr[1], "~") == 0)
	{
		ft_putstr_fd("minishell: cd: home not specified other than the \
		env var HOME, which isn't what Bash accesses for cd ~\n", 2);
		return ;
	}
	if (chdir(cmdarr[1]) < 0)
		perror("minishell: cd: ");
}

// Remember to, outside of the ft, check if more args than dest, then print error
// UPDATE: No, this ft is doing the check and printing error
// STDIN_FILENO: no. STDOUT_FILENO: no.
void	ft_cd(t_list *env, char **cmdarr)
{
	if (!cmdarr && !(*cmdarr))
		return ;
	if (too_many_args(cmdarr))
		return ;
	if (try_to_go_home_if_no_args(env, cmdarr) < 1)
		return ;
	try_to_go_to_path(env, cmdarr);
}
