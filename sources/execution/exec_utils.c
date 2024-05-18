#include "../../includes/minishell.h"

void    free_strarr(char **strarr)
{
    int i;

    i = -1;
    while (strarr[++i])
        free(strarr[i]);
    free(strarr);
    // *strarr = NULL; // this was causing "invalid write of size 8"
}

void	fork_one_for_simple_cmd(t_exe *b)
{
	b->smpl_cmd_pid = fork();
    if (b->smpl_cmd_pid < 0)
    {
        perror("fork");
        free_strarr(b->execve_argv);
        free_strarr(b->execve_envp);
    }
}

void	fork_one_in_ppl(t_exe *b)
{
	b->ppl_pids[b->i] = fork();
    if (b->ppl_pids[b->i] < 0)
    {
        perror("fork");
        free_strarr(b->execve_argv);
        free_strarr(b->execve_envp);
    }
}

void free_n_error_n_exit(char *errprefix, t_exe *b)
{
    if (errprefix)
        perror(errprefix);
    if (b->execve_path)
    {
        free(b->execve_path);
        b->execve_path = NULL;
    }
    if (b->execve_argv)
    {
        free_strarr(b->execve_argv);
        b->execve_path = NULL;
    }
    if (b->execve_envp)
    {
        free_strarr(b->execve_envp);
        b->execve_envp = NULL;
    }
    if (b->my_paths)
    {
        free_strarr(b->my_paths);
        b->my_paths = NULL;
    }
    exit(g_exit);
}