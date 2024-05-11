#include "../../includes/minishell.h"

void    lay_child_pipes(t_exe *b)
{
    if (b->i != b->ppl_cmd_count - 1) // if not last ppl_cmd, redir out
    {
        close(b->pp_fds[b->i % 2][0]);
        dup2(b->pp_fds[b->i % 2][1], STDOUT_FILENO);
        close(b->pp_fds[b->i % 2][1]);
    }
    if (b->i != 0) // if not 0th ppl_cmd, redir in
    {
        dup2(b->pp_fds[1 - (b->i % 2)][0], STDIN_FILENO);
        close(b->pp_fds[1 - (b->i % 2)][0]);
    }
}

// The 'if' checks whether we even need any reopening, i.e. more pipes
// Then the pipe which is not leading into child is reopened and points OUT.
int     reuse_pipe_in_parent(t_exe *b)
{
    // no closing for 1st cmd
    if (b->i == 0)
        ;
    // check if exactly 2nd cmd in ppln
    else if (b->i == 1)
    {
        if (close(b->pp_fds[1 - (b->i % 2)][1]) < 0)
            return (-1);
    }
    // all others
    else if (b->i > 1)
    {
        if (close(b->pp_fds[b->i % 2][0]) < 0 || \
            close(b->pp_fds[1 - (b->i % 2)][1]) < 0)
                return (-1);
        // if not last && reopen pipe. && as in "then"
        if (b->i != (b->ppl_cmd_count - 1) && \
            (pipe(b->pp_fds[b->i % 2]) < 0))
            return (-1);
    }
    return (0);
}
