#include "../../includes/minishell.h"

static void free_n_error_n_exit(char *errprefix, t_exe *b)
{
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
    if (errprefix)
        perror(errprefix);
    exit(g_exit);
}

void    exec_bin(t_ast *s, t_exe *b)
{
    if (set_up_redirs(s, b) == EXIT_FAILURE)
        return ;
    if (b->is_pipeline)
    {
        ++(b->i);
        reuse_pipe_in_parent(b);
        fork_one_in_ppl(b);
        if (b->ppl_pids[b->i] == 0)
        {
            prep_execve_args(s, b);
            lay_child_pipes(b);
            // slap_on_redirs;
            if (!b->execve_path || !b->execve_argv || !b->execve_envp || \
            slap_on_redirs_in_child(b) == EXIT_FAILURE)
                free_n_error_n_exit(NULL, b);
            execve(b->execve_path, b->execve_argv, b->execve_envp);
            free_n_error_n_exit("execve in a pipeline", b);
        }
        else
            clean_up_after_redirs_in_parent(b);
    }
    else
    {
        fork_one_for_simple_cmd(b);
        if (b->smpl_cmd_pid == 0)
        {
            prep_execve_args(s, b);
            // slap_on_redirs(s, b);
            if (!b->execve_path || !b->execve_argv || !b->execve_envp || \
            slap_on_redirs_in_child(b) < 0)
                free_n_error_n_exit(NULL, b);
            execve(b->execve_path, b->execve_argv, b->execve_envp);
            free_n_error_n_exit("execve for simple cmd", b);
        }
        else
        {
            clean_up_after_redirs_in_parent(b);
            waitpid(b->smpl_cmd_pid, &b->smpl_wstatus, 0);
            g_exit = (b->smpl_wstatus >> 8) & 0xFF;
        }
    }
    // g_exit = errno;
    // return (g_exit);
}