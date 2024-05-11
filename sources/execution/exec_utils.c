#include "../../includes/minishell.h"

void    seek_path(char *cmd, char **my_paths)
{
    int             i;
    char    *cmdpath;
    char    **cmdandopts;

    i = -1;
    cmdandopts = ft_split(cmd, ' ');
    if (!cmdandopts)
        fr1_perr_n_exit_errno(my_paths, "Malloc fail @ Ch_mid");
    while (my_paths[++i])
    {
        cmdpath = crt_cmdpath(my_paths[i], cmdandopts[0]);
        if (!cmdpath)
            fr2_perr_n_exit_errno(my_paths, cmdandopts, "Malloc \
                fail @ Ch_mid");
        if (access(cmdpath, X_OK) == 0)
            execve(cmdpath, cmdandopts, NULL);
        free(cmdpath);
    }
    perror(cmdandopts[0]);
    free_strarr(cmdandopts);
}

void    free_strarr(char **strarr)
{
    int i;

    i = -1;
    while (strarr[++i])
        free(strarr[i]);
    free(strarr);
    *strarr = NULL;
}

void	fork_one(t_exe *b)
{
	b->ppl_pids[b->i] = fork();
    if (b->ppl_pids[b->i] < 0)
    {
        perror("fork");
        free_strarr(b->execve_argv);
        free_strarr(b->execve_envp);
    }
}