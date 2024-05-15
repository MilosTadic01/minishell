#include "../../includes/minishell.h"

int    slap_on_redirs_in_child(t_exe *b)
{
    if (b->fd_redir_in > -1 && dup2(b->fd_redir_in, STDIN_FILENO) < 0)
    {
        perror("dup2 for redir_in_in");
        return (EXIT_FAILURE);
    }
    if (b->fd_redir_in > -1 && close(b->fd_redir_in) < 0)
    {
        perror("close hd_fd");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

void    clean_up_after_redirs_in_parent(t_exe *b)
{
    if (b->fd_redir_in > -1 && close(b->fd_redir_in) < 0)
        perror("close fail of fd_redir_in in parent");
    b->fd_redir_in = -1;
    if (b->fd_redir_out > -1 && close(b->fd_redir_out) < 0)
        perror("close fail of fd_redir_out in parent");
    b->fd_redir_out = -1;
}