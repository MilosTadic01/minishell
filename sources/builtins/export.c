#include "../../includes/minishell.h"

static void del_if_already_an_envvar(int keylen, char *kv_str, t_list **env)
{
    t_list  *cpy;

    if (!env || !(*env) || !kv_str)
        return ;
    cpy = *env;
    while (cpy)
    {
        if (ft_strncmp(cpy->as_str, kv_str, keylen) == 0 && \
            cpy->as_str[keylen] == '=')
        {
            ft_unset(kv_str, env);
            break ;
        }
        cpy = cpy->next;
    }
}

static int extract_keylen(char *kv_str)
{
    int i;

    i = -1;
    if (kv_str[0] == '=')
    {
        ft_putstr_fd("minishell: export: ", STDERR_FILENO);
        ft_putstr_fd(kv_str, STDERR_FILENO);
        ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
        return (0);
    }
    while (kv_str[++i])
    {
        if (kv_str[i] == '=')
            return (i);
    }
    return (0);
}

void    ft_export(char *kv_str, t_list **env)
{
    t_type  tmp;
    int     keylen;

    keylen = extract_keylen(kv_str);
    if (keylen == 0 || !env) // not checking for !(*env) in case the env is empty I guess? lst_addback takes care of that.
        return ;
    del_if_already_an_envvar(keylen, kv_str, env);
    tmp = (t_type){.as_str = kv_str};
    ft_lstadd_back(env, ft_lstnew(&tmp, AS_STR));
}

int export_cmdarr(int size, char **cmdarr, t_list **env)
{
    int     i;

    if (!cmdarr || !(*cmdarr) || !env || !(*env))
        return (1);
    i = 0;
    while (++i < size)
    {
        ft_export(cmdarr[i], env);
    }
    return (SUCCESS);
}