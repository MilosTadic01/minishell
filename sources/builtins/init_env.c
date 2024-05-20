/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 01:14:34 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/03 13:24:41 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_shlvl(t_list **env)
{
	int		shlvl;
	char	*str;
	char	*num;

	if (ft_getenv("SHLVL", *env))
	{
		shlvl = ft_atoi(ft_getenv("SHLVL", *env)) + 1;
		num = ft_itoa(shlvl);
		str = ft_strjoin("SHLVL=", num);
		ft_export(str, env);
		free(str);
		free(num);
	}
	else
		ft_export("SHLVL=1", env);
}

static char	*getcwd_naive(void)
{
	char	*buff;
	char	*pwd;

	buff = NULL;
	pwd = NULL;
	buff = malloc(PATH_MAX * sizeof(char));
	if (!buff)
		ft_putstr_fd("minishell: cwd_naive: malloc\n", STDERR_FILENO);
	else
	{
		pwd = getcwd(buff, PATH_MAX);
		if (pwd == NULL)
			perror("minishell: cwd_naive: ");
	}
	return (pwd);
}

static void	set_pwd(t_list **env)
{
	char	*newpwd;
	char	*cwd;

	cwd = getcwd_naive();
	newpwd = ft_strjoin("PWD=", cwd);
	ft_export(newpwd, env);
	free(cwd);
	free(newpwd);
}

static void	set_shell(t_list **env)
{
	if (ft_strcmp(ft_getenv("SHELL", *env), "minishell") != 0)
		ft_export("SHELL=minishell", env);
}

t_list	*init_env(char **envp)
{
	t_list	*env;
	t_type	tmp;
	int		i;

	i = -1;
	env = NULL;
	while (envp[++i])
		;
	while (--i >= 0)
	{
		tmp = (t_type){.as_str = envp[i]};
		ft_lstadd_back(&env, ft_lstnew(&tmp, AS_STR));
	}
	set_shell(&env);
	set_pwd(&env);
	set_shlvl(&env);
	return (env);
}
