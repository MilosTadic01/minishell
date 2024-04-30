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
    int     i;
    t_list  *pwd;

    ft_unset(env, "SHELL");
    i = -1;
    pwd = NULL;
    while (*env)
    {
        if (strncmp(*env, "SHELL=", 6) == 0 && 
            strncmp((*env)->as_str[6], "minishell", 9) != 0)
        {
            ft_unset(env);
            ft_export(env, "SHELL=minishell")
        }
        else if (strncmp(env[i], "PWD=", 4))
            pwd = env[i];
    }
    if (!pwd)
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

// All this sh** needs some serious t_list dereferencing review.

// Which data bus to use? data->env is placeholder
// void    extract_entire_env(t_data *data, char **envp)
// {
//     int i;
//     t_lst *head;

//     i = -1;
//     while(envp[++i])
//         ft_lstadd_back(&head, ft_lstnew(envp[i]));
//     //
//     data->env = head;
// }

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

static int is_it_already_an_envvar(t_list *env, char *key)
{
    ;
}

static char *extract_key(char *kv_str)
{
    int i;
    
    i = -1;
    if (kv_str[0] == '=')
    {
        ft_putstr_fd("minishell: export: ", STDERR_FILENO);
        ft_putstr_fd(kv_str, STDERR_FILENO);
        ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
        return (NULL);
    }
    while (kv_str[++i])
    {
        if (i > 0 && kv_str[i] == '=')
            return (&kv_str[i]);
    }
}

void    ft_export(t_list **env, char *kv_str)
{
    t_list  *cpy;
    int     len;
    char    *key;

    cpy = *env;
    key = extract_key(kv_str);
    if (!key)
        return ;
    len = ft_strlen(key);
    while (cpy)
    {
        if (ft_strncmp(cpy->as_str, key, len) == 0)
        {
            ft_unset(env, kv_str)
        }
        cpy = cpy->next;
    }
    if (ft_strchr(cpy->as_str, '='))
    {
        if (kv_str[0] == '=')
        {
            ft_putstr_fd("minishell: export: ", STDERR_FILENO);
            ft_putstr_fd(kv_str, STDERR_FILENO);
            ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
        }
        else
            ft_lstadd_back((*env)->as_str, ft_lstnew(kv_str));
    }
}

static void	ft_lstdeloneenv(t_list **envvar, t_list **prev)
{
	if (!envvar || !(*envvar))
		return ;
    if (*prev)
        (*prev)->next = (*envvar)->next;
    free (*envvar);
	*envvar = NULL;
	return ;
}

void    ft_unset(t_list **env, char *str)
{
    int     len;
    t_list  *current;
    t_list  *prev;

    len = ft_strlen(str);
    prev = NULL;
    current = *env;
    while (current)
    {
        if (strncmp(current->as_str, str, len) == 0 && \
            current->as_str[len] == '=')
        {
            ft_lstdeloneenv(&current, &prev);
            break ;
        }
        prev = current;
        current = current->next;
    }
}