#include "../../includes/minishell.h"

void    exec_bin(t_ast *s, t_exe *b)
{
    set_up_redirs(s, b);
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
            if (!b->execve_path || !b->execve_argv || !b->execve_envp || 
                slap_on_redirs_in_child(s, b) == EXIT_FAILURE)
                free_n_error_n_exit(NULL, b);
            execve(b->execve_path, b->execve_argv, b->execve_envp);
            free_n_error_n_exit(b->execve_argv[0], b);
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
            slap_on_redirs_in_child(s, b) == EXIT_FAILURE)
                free_n_error_n_exit(NULL, b);
            execve(b->execve_path, b->execve_argv, b->execve_envp);
            free_n_error_n_exit(b->execve_argv[0], b);
        }
        else
        {
            clean_up_after_redirs_in_parent(b);
            receive_signals_noninteractive();
            waitpid(b->smpl_cmd_pid, &b->smpl_wstatus, 0);
            receive_signals_interactive();
            g_exit = (b->smpl_wstatus >> 8) & 0xFF;
        }
    }
    // receive_signals_interactive();
    // g_exit = errno;
    // return (g_exit);
}