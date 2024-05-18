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
    return (0);
}

static void exec_builtin_in_pipeline(int builtin, t_ast *s, t_exe *b)
{
    ++(b->i);
    reuse_pipe_in_parent(b);
    fork_one_in_ppl(b);
    if (b->ppl_pids[b->i] == 0)
    {
        lay_child_pipes(b);
        if (slap_on_redirs_in_child(s, b) == EXIT_FAILURE)
            exit(g_exit);
        g_exit = call_builtin(builtin, s, b);
        exit(g_exit);
    }
    else
        clean_up_after_redirs_in_parent(b);
}

static void exec_echo_in_child(int builtin, t_ast *s, t_exe *b)
{
    fork_one_for_simple_cmd(b);
    if (b->smpl_cmd_pid == 0)
    {
        if (slap_on_redirs_in_child(s, b) == EXIT_FAILURE)
            exit(1);
        g_exit = call_builtin(builtin, s, b);
        exit(g_exit);
    }
    else
    {
        clean_up_after_redirs_in_parent(b);
        waitpid(b->smpl_cmd_pid, &b->smpl_wstatus, 0);
        g_exit = (b->smpl_wstatus >> 8) & 0xFF;
    }
}

static void exec_builtin_in_parent(int builtin, t_ast *s, t_exe *b)
{
    g_exit = call_builtin(builtin, s, b);
    clean_up_after_redirs_in_parent(b);
}

void    exec_builtin(int builtin, t_ast *s, t_exe *b)
{
    set_up_redirs(s, b);
    if (b->is_pipeline)
        exec_builtin_in_pipeline(builtin, s, b);
    else if ((s->command->ins || s->command->outs) && builtin == ECHO)
        exec_echo_in_child(builtin, s, b);
    else
        exec_builtin_in_parent(builtin, s, b);
}