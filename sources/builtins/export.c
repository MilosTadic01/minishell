#include "../../includes/minishell.h"

static void del_if_already_an_envvar(t_list **env, char *kv_str, int keylen)
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
            ft_unset(env, kv_str);
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

void    ft_export(t_list **env, char *kv_str)
{
    t_type  tmp;
    int     keylen;

    keylen = extract_keylen(kv_str);
    if (keylen == 0 || !env) // not checking for !(*env) in case the env is empty I guess? lst_addback takes care of that.
        return ;
    del_if_already_an_envvar(env, kv_str, keylen);
    tmp = (t_type){.as_str = kv_str};
    ft_lstadd_back(env, ft_lstnew(&tmp, AS_STR));
}

void    export_cmdarr(t_list **env, char **cmdarr)
{
    int     i;

    if (!cmdarr || !(*cmdarr) || !env || !(*env))
        return ;
    i = 0;
    while (cmdarr[++i])
    {
        ft_export(env, cmdarr[i]);
    }
}