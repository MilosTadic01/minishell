#include "../../includes/minishell.h"

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