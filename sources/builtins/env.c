/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 01:14:34 by mitadic           #+#    #+#             */
/*   Updated: 2024/04/21 01:15:51 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void    set_core_env(t_list **env)
{
    char	buff[PATH_MAX];
	char	*str;
    // int     shlvl;

    if (ft_strcmp(ft_getenv(*env, "SHELL"), "minishell"))
        ft_export(env, "SHELL=minishell");
    str = NULL;
    str = ft_strjoin("PWD=", getcwd(buff, PATH_MAX));
    ft_export(env, str);
    free(str);
    // ADD FT_ITOA FOR THIS
    // if (ft_getenv(*env, "SHLVL"))
    // {
    //     shlvl = ft_atoi(ft_getenv(*env, "SHLVL")) + 1;
    //     str = ft_strjoin("SHLVL=", ft_itoa(shlvl));
    //     ft_export(env, str);
    //     free(str);
    // }
    // else
    //     ft_export(env, "SHLVL=1");
}

t_list  *init_env(char **envp)
{
    t_list  *env;
    t_type  tmp;
    int     i;
    
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

void    ft_printenv(t_list *env)
{
    while (env)
    {
        ft_putstr_fd(env->as_str, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        env = env->next;
    }
}

char    *ft_getenv(t_list *env, char *key)
{
    int len;

    len = ft_strlen(key);
    while (env)
    {
        if (ft_strncmp(env->as_str, key, len) == 0 &&\
            env->as_str[len] == '=')
            return (&env->as_str[len + 1]); // return string, i.e. char*, not char, huh?
        env = env->next;
    }
    return (NULL);
}

// // for this I'm gonna need Darias [cmd] [arg] [arg] [arg]... But for now I'm just assuming it's a strarr
// void    ft_printenv(t_list *env, char **varkeys)
// {
//     int i;
//     char *varval;
//     int len;

//     i = 0;
//     while (varkeys[++i])
//     {
//         len = ft_strlen(varkeys[i]);
//         varval = ft_getenv(env, varkeys[i]);
//         if (varval)
//         {
//             ft_putstr_fd(&(env->content)[len], STDOUT_FILENO);
//             ft_putstr_fd("\n", STDOUT_FILENO);
//         }
//     }
// }