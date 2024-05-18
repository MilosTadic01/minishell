#include "../../includes/minishell.h"

static void  set_up_redir_outs(t_ast *s, t_exe *b)
{
    if (s->command->outs)
    {
        if (open_all_outfiles(s, b) == EXIT_FAILURE)
            return ;
    }
}

static void set_up_redir_ins(t_ast *s, t_exe *b)
{
    int     hd_count;

    if (s->command->ins)
    {
        hd_count = count_hds_in_this_cmd(s);
        infile_legitimacy_control(s, b, hd_count);
        // if (infile_legitimacy_control(s, b, hd_count) == EXIT_FAILURE)
        //     return ;
        locate_last_infile_and_open_it(s, b);
    }
}

void    set_up_redirs(t_ast *s, t_exe *b)
{
    if (!s->command->ins && !s->command->outs)
        return ;
    set_up_redir_ins(s, b);
    set_up_redir_outs(s, b);
}