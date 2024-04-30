#include "../../includes/minishell.h"

// if *prev then bypass nodecopy, else head->next becomes head.
// then free the nodecopy.
static void	ft_lstdeloneenv(t_list **envvar, t_list **prev)
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

void    ft_unset(t_list **env, char *kv_str)
{
    int     len;
    t_list  *current;
    t_list  *prev;

    if (!kv_str || !env || !(*env))
        return ;
    len = ft_strlen(kv_str);
    prev = NULL;
    current = *env;
    while (current)
    {
        if (strncmp(current->as_str, kv_str, len) == 0 && \
            current->as_str[len] == '=')
        {
            ft_lstdeloneenv(&current, &prev);
            break ;
        }
        prev = current;
        current = current->next;
    }
}