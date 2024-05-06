#include "../../includes/minishell.h"

int    ft_printenv(t_list *env)
{
    if (!env)
        return (1);
    while (env)
    {
        ft_putstr_fd(env->as_str, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        env = env->next;
    }
    return (SUCCESS);
}

char    *ft_getenv(char *key, t_list *env)
{
    int len;

    if (!key || !env)
        return (NULL);
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