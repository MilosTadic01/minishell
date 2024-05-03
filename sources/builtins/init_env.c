/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 01:14:34 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/03 13:24:41 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void set_shlvl(t_list **env)
{
    int     shlvl;
    char	*str;
    char    *num;

    if (ft_getenv(*env, "SHLVL"))
    {
        shlvl = ft_atoi(ft_getenv(*env, "SHLVL")) + 1;
        num = ft_itoa(shlvl);
        str = ft_strjoin("SHLVL=", num);
        ft_export(env, str);
        free(str);
        free(num);
    }
    else
        ft_export(env, "SHLVL=1");
}

static void set_pwd(t_list **env)
{
    char    *str;

    str = ft_strjoin("PWD=", ft_getcwd());
    ft_export(env, str);
    free(str);
}

static void set_shell(t_list **env)
{
    if (ft_strcmp(ft_getenv(*env, "SHELL"), "minishell") != 0)
        ft_export(env, "SHELL=minishell");
}

static void    set_core_env(t_list **env)
{
    set_shell(env);
    set_pwd(env);
    set_shlvl(env);
}

t_list  *init_env(char **envp)
{
    t_list  *env;
    t_type  tmp;
    int     i;

    // if (!envp) Q for Daria: can this ever be the case? the env can be empty, sure, but can the (...global...?) variable ever not exist?
    //     ;
    i = -1;
    env = NULL;
    while(envp[++i])
        ;
    while(--i >= 0)
    {
        tmp = (t_type){.as_str = envp[i]};
        ft_lstadd_back(&env, ft_lstnew(&tmp, AS_STR));
    }
    set_core_env(&env);
    return (env);
}