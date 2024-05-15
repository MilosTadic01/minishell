#include "../../includes/minishell.h"

static int reopen_hd_file_for_reading(t_exe *b, int i)
{
    char    *num;
    char    *path;

    num = ft_itoa(i);
    path = ft_strjoin("/tmp/heredoc", num);
    free(num);
    b->fd_redir_in = open(path, O_RDONLY, 0644);
    free(path);
    if (b->fd_redir_in < 0)
    {
        perror("heredoc: ");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

static void locate_last_infile_and_open_it(t_ast *s, t_exe *b)
{
    t_list  *last_in;
    t_list  *ins_cpy;

    last_in = s->command->ins;
    ins_cpy = s->command->ins;
    while (ins_cpy)
    {
        if (ins_cpy->as_item->type == REDIRECT_IN_IN)
            (b->hd_idx)++;
        last_in = ins_cpy;
        ins_cpy = ins_cpy->next;
    }
    if (last_in->as_item->type == REDIRECT_IN_IN)
        reopen_hd_file_for_reading(b, b->hd_idx);
    else if (last_in->as_item->type == REDIRECT_IN)
    {
        b->fd_redir_in = open(last_in->as_item->filename, O_RDONLY);
        if (b->fd_redir_in < 0)
            perror("open for redir_in");
    }
}

static int  count_hds_in_this_cmd(t_ast *s)
{
    t_list  *ins_cpy;
    int hds;

    hds = 0;
    ins_cpy = s->command->ins;
    while (ins_cpy)
    {
        if (ins_cpy->as_item->type == REDIRECT_IN_IN)
            hds++;
        ins_cpy = ins_cpy->next;
    }
    return (hds);
}

static int  are_all_infiles_legit(t_ast *s)
{
    t_list  *ins_cpy;

    ins_cpy = s->command->ins;
    while (ins_cpy)
    {
        if (ins_cpy->as_item->type == REDIRECT_IN)
        {
            if (access(ins_cpy->as_item->filename, R_OK) != 0)
            {
                ft_putstr_fd("minishell: ", STDERR_FILENO);
                perror(ins_cpy->as_item->filename);
                return (0);
            }
        }
        ins_cpy = ins_cpy->next;
    }
    return (1);
}

void    set_up_redirs(t_ast *s, t_exe *b)
{
    int     hd_count;

    if (!s->command->ins && !s->command->outs)
        return ;
    hd_count = count_hds_in_this_cmd(s);
    if (!are_all_infiles_legit(s))
    {
        b->hd_idx += hd_count;
        b->fd_redir_in = -1;
        return ;
    }
    else
        locate_last_infile_and_open_it(s, b);
}