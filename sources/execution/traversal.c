#include "../../includes/minishell.h"

static int  which_builtin(char *str)
{
    if (!ft_strcmp(str, "echo"))
        return (ECHO);
    if (!ft_strcmp(str, "cd"))
        return (CD);
    if (!ft_strcmp(str, "pwd"))
        return (PWD);
    if (!ft_strcmp(str, "export"))
        return (EXPORT);
    if (!ft_strcmp(str, "unset"))
        return (UNSET);
    if (!ft_strcmp(str, "env"))
        return (ENV);
    if (!ft_strcmp(str, "exit"))
        return (EXIT);
    return (0);
}

static void close_pipes_and_wait_and_reset_pipeline(t_exe *b)
{
    pipe_closer(b);
    go_wait(b);
    b->is_pipeline = 0;
}

static int  command_exec(t_ast *s, t_exe *b)
{
    int builtin;

    builtin = 0;
    if (!s || !s->command || !s->command->args)
        return (g_exit);
    if (!b->log_op || b->log_op == PIPE || \
        (b->log_op == AND && g_exit == 0) || \
        (b->log_op == OR && g_exit > 0))
    {
        builtin = which_builtin(s->command->args[0]);
        if (builtin)
            return (exec_builtin(builtin, s, b)); // TODO: ditch return bc pipeline exit
        else
            return (exec_bin(s, b));
    }
    return (g_exit); // retain the value of g_exit if not executing
}

int    traverse_ast_to_exec(t_ast *s, t_exe *b)
{
    if (s->tag == COMMAND)
        g_exit = command_exec(s, b);
    else if (s->tag == SUBSHELL || s->tag == RECCALL)
        g_exit = minishell(s->subshell_cmd, b->env);
    else
    {
        // count pipes, set is_pipeline to True
        if (s->op == PIPE && b->is_pipeline == 0)
            set_up_pipeline(s, b);
        if (s->left)
            g_exit = traverse_ast_to_exec(s->left, b);
        b->log_op = s->op; // assign / update log_op before going right
        if (b->is_pipeline == 1 && s->right != NULL && \
        (s->right->op == AND || s->right->op == OR)) // bottom of ppl for currently parsed command
            close_pipes_and_wait_and_reset_pipeline(b);
        if (s->right)
            g_exit = traverse_ast_to_exec(s->right, b);
    }
    if (b->is_pipeline == 1 && (b->i == b->ppl_cmd_count - 1)) // bottom of pipeline
        close_pipes_and_wait_and_reset_pipeline(b);
    return (g_exit); // right?
}