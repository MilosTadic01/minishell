#include "../../includes/minishell.h"

// if *prev then bypass nodecopy, else head->next becomes head.
// then free the nodecopy.

static int extract_keylen(char *kv_str)
{
    int i;

    i = -1;
    while (kv_str[++i])
    {
        if (kv_str[i] == '=')
            return (i);
    }
    return (0);
}

static void	deloneenv(t_list **envvar, t_list **prev)
{
    t_list  *nodecopy;

	if (!envvar || !(*envvar))
		return ;
    nodecopy = *envvar;
    if (prev && *prev)
        (*prev)->next = (*envvar)->next;
    else
        *envvar = (*envvar)->next;
    free (nodecopy);
	return ;
}

void    ft_unset(char *kv_str, t_list **env)
{
    int     len;
    t_list  *current;
    t_list  *prev;

    len = extract_keylen(kv_str);
    prev = NULL;
    current = *env;
    while (current)
    {
        if (strncmp(current->as_str, kv_str, len) == 0 && \
            current->as_str[len] == '=')
        {
            deloneenv(&current, &prev);
            break ;
        }
        prev = current;
        current = current->next;
    }
}

// cmdarr[0] == "unset"
int unset_cmdarr(int size, char **cmdarr, t_list **env)
{
    int     i;

    if (!cmdarr || !(*cmdarr) || !env || !(*env))
        return (1);
    i = 0;
    while (++i < size)
    {
        ft_unset(cmdarr[i], env);
    }
    return (SUCCESS);
}