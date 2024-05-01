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
    int     shlvl;
    char    *num;

    if (ft_strcmp(ft_getenv(*env, "SHELL"), "minishell"))
        ft_export(env, "SHELL=minishell");
    str = NULL;
    str = ft_strjoin("PWD=", getcwd(buff, PATH_MAX));
    ft_export(env, str);
    free(str);
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