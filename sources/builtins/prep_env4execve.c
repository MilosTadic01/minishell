#include "../../includes/minishell.h"

char    **ft_prepenv(t_list *env)
{
    char    **strarr;
    int     size;
    int     i;

    size = ft_lstsize(env);
    strarr = malloc((size + 1) * sizeof(char *));
    if (!strarr)
    {
        perror("minishell: for execve: malloc fail for envp: ");
        return (NULL);
    }
    i = -1;
    while (env)
    {
        strarr[++i] = env->as_str;
        env = env->next;
    }
    strarr[++i] = NULL;
    return (strarr);
}