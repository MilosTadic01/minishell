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

static void loop_thru_path_possibilities(t_exe *b)
{
    int i;

    i = -1;
    while (b->my_paths[++i])
    {
        b->execve_path = crt_cmdpath(b->my_paths[i], b->execve_argv[0]);
        if (!b->execve_path)
            free_n_error_n_exit("crt_cmdpath() fail", b);
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

void    seek_path(t_exe *b)
{
    b->execve_path = 0;
    if (b->execve_argv[0] == NULL)
        return ;
    if (access(b->execve_argv[0], X_OK) == 0)
    {
        b->execve_path = b->execve_argv[0];
        return ;
    }
    b->my_paths = ft_split(ft_getenv("PATH", *(b->env)), ':');
    if (!b->my_paths)
        free_n_error_n_exit("Malloc fail @ path split", b);
    loop_thru_path_possibilities(b);
}
