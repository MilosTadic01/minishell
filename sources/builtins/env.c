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

#include "builtins.h"

// All this sh** needs some serious t_list dereferencing review.

// Which data bus to use? data->env is placeholder
void    extract_entire_env(t_data *data, char **envp)
{
    int i;
    t_list *head;

    i = -1;
    while(envp[++i])
        ft_lstadd_back(&head, ft_lstnew(envp[i]));
    //
    data->env = head;
}

void    ft_env(t_list *env)
{
    while (env)
    {
        ft_putstr_fd((char *)env->content, STDOUT_FILENO);
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
        if (ft_strncmp(*(char *)env->content, key, len) == 0 && \
            *(char *)(env->content)[len] == '=')
            return (&(char *)(env->content)[len + 1]); // return string, i.e. char*, not char, huh?
        env = env->next;
    }
    return (NULL);
}

// for this I'm gonna need Darias [cmd] [arg] [arg] [arg]... But for now I'm just assuming it's a strarr
void    ft_printenv(t_list *env, char **varkeys)
{
    int i;
    char *varval;
    int len;

    i = 0;
    while (varkeys[++i])
    {
        len = ft_strlen(varkeys[i]);
        varval = ft_getenv(env, varkeys[i]);
        if (varval)
        {
            ft_putstr_fd(&(env->content)[len], STDOUT_FILENO);
            ft_putstr_fd("\n", STDOUT_FILENO);
        }
    }
}

void    ft_export(t_data *data, char **kv_pairs)
{
    int i;

    i = 0;
    while (kv_pairs[++i])
    {
        if (ft_strchr(kv_pairs[i], '='))
        {
            if (kv_pairs[i][0] == '=')
            {
                ft_putstr_fd("minishell: export: ", STDERR_FILENO);
                ft_putstr_fd(kv_pairs[i], STDERR_FILENO);
                ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
            }
            else
                ft_lstadd_back(&data->env, ft_lstnew(kv_pairs[i]));
        }
    }
}

void    ft_unset(t_data *data, char *str)
{

}