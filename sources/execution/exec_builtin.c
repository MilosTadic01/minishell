#include "../../includes/minishell.h"

static int call_builtin(int builtin, t_ast *s, t_exe *b)
{
    if (builtin == ECHO)
        return (ft_echo(s->command->size, s->command->args));
    if (builtin == CD)
        return (ft_cd(s->command->size, s->command->args, b->env));
    if (builtin == PWD)
        return (ft_pwd());
    if (builtin == EXPORT)
        return (export_cmdarr(s->command->size, s->command->args, b->env));
    if (builtin == UNSET)
        return (unset_cmdarr(s->command->size, s->command->args, b->env));
    if (builtin == ENV)
        return (ft_printenv(*(b->env)));
    if (builtin == EXIT)
        return (ft_exit(s->command->size, s->command->args));
    return (1);
}

// TODO: slap on redirs
void    exec_builtin(int builtin, t_ast *s, t_exe *b)
{
    if (b->is_pipeline)
    {
        ++(b->i);
        reuse_pipe_in_parent(b);
        fork_one_in_ppl(b);
        if (b->ppl_pids[b->i] == 0)
        {
            lay_child_pipes(b);
            // slap_on_redirs(s, b);
            g_exit = call_builtin(builtin, s, b);
            exit(g_exit);
        }
        // else // currently ignoring this idea, bc in a ppl, builtins are forked for
        //     b->ppl_pids[b->i] = -1;
        return ; // had to add some return value here, doesn't seem right, but neither does error value
    }
    else
        call_builtin(builtin, s, b);
}