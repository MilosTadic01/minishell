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
    // if (b->is_subshell == 0)
    b->is_pipeline = 0;
    b->ppl_cmd_count = 0;
}

static void increment_hd_idx(t_ast *s, t_exe *b)
{
    t_list *ins_cpy;

    ins_cpy = s->command->ins;
    while (ins_cpy)
    {
        if (ins_cpy->as_item->type == REDIRECT_IN_IN)
            (b->hd_idx)++;
        ins_cpy = ins_cpy->next;
    }
}

static void command_exec(t_ast *s, t_exe *b)
{
    int builtin;

    builtin = 0;
    if (!s || !s->command || !s->command->args)
        return ;
    if (!b->log_op || b->log_op == PIPE || \
        (b->log_op == AND && g_exit == 0) || \
        (b->log_op == OR && g_exit > 0))
    {
        builtin = which_builtin(s->command->args[0]);
        if (builtin)
            exec_builtin(builtin, s, b); // TODO: ditch return bc pipeline exit
        else
            exec_bin(s, b);
    }
    else
        increment_hd_idx(s, b);
    // return (g_exit); // retain the value of g_exit if not executing
}

void    traverse_ast_to_exec(t_ast *s, t_exe *b)
{
    if (s->tag == COMMAND)
        command_exec(s, b);
    else if (s->tag == SUBSHELL || s->tag == RECCALL)
    {
        ++(b->is_subshell);
        minishell(s->subshell_cmd, b, b->env);
        --(b->is_subshell);
    }
    else
    {
        // count pipes, set is_pipeline to True
        if (s->op == PIPE && b->is_pipeline == 0)
            set_up_pipeline(s, b);
        if (s->left)
            traverse_ast_to_exec(s->left, b);
        b->log_op = s->op; // assign / update log_op before going right
        if (b->is_pipeline == 1 && s->right != NULL && \
        ((s->right->tag == BINOP && s->right->op == AND) || (s->right->tag == BINOP && s->right->op == OR))) // bottom of ppl for currently parsed command
            close_pipes_and_wait_and_reset_pipeline(b);
        if (s->right)
            traverse_ast_to_exec(s->right, b);
    }
    if (b->is_pipeline == 1 && (b->i == b->ppl_cmd_count - 1)) // bottom of pipeline
        close_pipes_and_wait_and_reset_pipeline(b);
    // return (g_exit); // right?
}