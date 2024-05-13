#include "../../includes/minishell.h"

static char *crt_cmdpath(char *path, char *cmd)
{
    char    *concat_step1;
    char    *concat_step2;

    concat_step1 = ft_strjoin(path, "/");
    if (!concat_step1)
        return (NULL);
    concat_step2 = ft_strjoin(concat_step1, cmd);
    free(concat_step1);
    if (!concat_step2)
        return (NULL);
    return (concat_step2);
}

void    seek_path(t_exe *b)
{
    int             i;

    i = -1;
    b->my_paths = ft_split(ft_getenv("PATH", *(b->env)), ':');
    if (!b->my_paths)
        ft_putstr_fd("Malloc fail @ path split\n", 2); // free execve_argv n exit
    while (b->my_paths[++i])
    {
        b->execve_path = crt_cmdpath(b->my_paths[i], b->execve_argv[0]);
        if (!b->execve_path)
            ft_putstr_fd("crt_cmdpath() fail\n", 2); // free execve_argv, execve_mypaths, n exit
        if (access(b->execve_path, X_OK) == 0)
            break ;
        free(b->execve_path);
        b->execve_path = NULL;
    }
    if (!b->execve_path)
    {
        perror(b->execve_argv[0]);
        g_exit = errno;
    }
}
