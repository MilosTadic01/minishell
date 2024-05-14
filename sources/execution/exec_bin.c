#include "../../includes/minishell.h"

static void free_n_error_n_exit(char *errprefix)
{
    // free
    perror(errprefix);
    exit(errno);
}

int    exec_bin(t_ast *s, t_exe *b)
{
    // idea (red thread of returns): if (prep) != 0, print error then set g_exit and return
    // alternative: fork before prep, then you can exit anywhere
    // tricky to get pid for pipeline into the pid_array if 
    // prep_execve_args(s, b);
    // CURRENT: moved the prep inside the child processes
    if (b->is_pipeline)
    {
        ++(b->i);
        reuse_pipe_in_parent(b);
        fork_one_in_ppl(b);
        if (b->ppl_pids[b->i] == 0)
        {
            prep_execve_args(s, b);
            lay_child_pipes(b);
            // slap_on_redirs(s, b);
            if (!b->execve_path || !b->execve_argv || !b->execve_envp)
                exit (errno); // what value to give?
            execve(b->execve_path, b->execve_argv, b->execve_envp);
            free_n_error_n_exit("execve in a pipeline");
        }
    }
    else
    {
        fork_one_for_simple_cmd(b);
        if (b->smpl_cmd_pid == 0)
        {
            prep_execve_args(s, b);
            // slap_on_redirs(s, b);
            if (!b->execve_path || !b->execve_argv || !b->execve_envp)
                exit (errno); // what value to give?
            execve(b->execve_path, b->execve_argv, b->execve_envp);
            free_n_error_n_exit("execve for simple cmd");
        }
        else
            waitpid(b->smpl_cmd_pid, &b->smpl_wstatus, 0);
    }
    g_exit = errno;
    return (g_exit);
}