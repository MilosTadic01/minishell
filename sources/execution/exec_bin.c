#include "../../includes/minishell.h"

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
            execve(b->execve_path, b->execve_argv, b->execve_envp);
        }
    }
    else
    {
        fork_one_for_simple_cmd(b);
        if (b->smpl_cmd_pid == 0)
        {
            prep_execve_args(s, b);
            // slap_on_redirs(s, b);
            execve(b->execve_path, b->execve_argv, b->execve_envp);
        }
        wait(&b->smpl_wstatus);
    }
    g_exit = errno;
    return (g_exit);
}