#include "../../includes/minishell.h"

// Would real shell abort if (wpid[i] < 0) ?
// void    go_wait(int prcs_count, pid_t *child, char **my_paths)
// {
//     int             i;
//     pid_t   *wpid;
//     int             *status;

//     i = -1;
//     wpid = (pid_t *)malloc(sizeof(pid_t) * prcs_count);
//     status = (int *)malloc(sizeof(int) * prcs_count);
//     if (!wpid || !status)
//         purge_waiter(wpid, status, my_paths, child);
//     while (++i < prcs_count)
//     {
//         wpid[i] = waitpid(child[i], &status[i], 0);
//         if (wpid[i] < 0)
//             purge_waiter(wpid, status, my_paths, child);
//     }
//     free(wpid);
//     free(status);
// }

void    go_wait(t_exe *b)
{
    int     i;
    // pid_t   *wpid;

    i = -1;
    // wpid = malloc(b->ppl_cmd_count * sizeof(pid_t));
    while (++i < b->ppl_cmd_count)
    {
        // if (b->ppl_pids[b->i] == -1) // currently ignoring this idea, bc in a ppl, builtins are forked for
        //     continue ;
        // receive_signals_noninteractive();
        // wpid[i] = waitpid(b->ppl_pids[i], &b->ppl_wstatuses[i], 0);
        waitpid(b->ppl_pids[i], &b->ppl_wstatuses[i], 0);
        // receive_signals_interactive();
        // if (wpid[i] < 0)
        //     ft_putstr_fd("waitpid: error\n", 2);
    }
    if (i > 0)
        g_exit = (b->ppl_wstatuses[i - 1] >> 8) & 0xFF;
    // free(wpid);
    free(b->ppl_pids);
    free(b->ppl_wstatuses);
}