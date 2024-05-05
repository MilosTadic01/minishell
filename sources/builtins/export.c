#include "../../includes/minishell.h"

static void del_if_already_an_envvar(int keylen, char *kv_str, t_list **env)
{
    char    *key;

    if (!env || !(*env) || !kv_str)
        return ;
    key = ft_substr(kv_str, 0, keylen);
    ft_unset(key, env);
    free(key);
}

static int  is_invalid_key(int keylen, char *kv_str)
{
    int i;

    i = -1;
    while (++i < keylen)
    {
        if (!(ft_isalnum(kv_str[i])) && kv_str[i] != '_')
        {
            ft_putstr_fd("minishell: export: ", STDERR_FILENO);
            ft_putstr_fd(kv_str, STDERR_FILENO);
            ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
            return (1);
        }
    }
    return (0);
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

int ft_export(char *kv_str, t_list **env)
{
    t_type  tmp;
    int     keylen;

    if (!kv_str || !env) // not checking for !(*env) in case the env is empty I guess? lst_addback takes care of that.
        return (SUCCESS);
    keylen = extract_keylen(kv_str);
    if (is_invalid_key(keylen, kv_str))
        return (1);
    del_if_already_an_envvar(keylen, kv_str, env);
    tmp = (t_type){.as_str = kv_str};
    ft_lstadd_back(env, ft_lstnew(&tmp, AS_STR));
    return (SUCCESS);
}

int export_cmdarr(int size, char **cmdarr, t_list **env)
{
    int     i;

    if (!cmdarr || !(*cmdarr) || !env || !(*env))
        return (1);
    i = 0;
    while (++i < size)
    {
        if (ft_export(cmdarr[i], env) != SUCCESS)
            return (1);
    }
    return (SUCCESS);
}