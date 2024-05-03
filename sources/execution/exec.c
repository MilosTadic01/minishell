#include "../../includes/minishell.h"

static void init_exe_bus(t_exe *exe_bus, t_list **env)
{
    exe_bus->env = env;
    exe_bus->heredoc_fds = NULL;
    exe_bus->heredoc_count = 0;
    exe_bus->pids = NULL;
    exe_bus->log_op = 0;
}

void    exec(t_ast *s, t_list **env)
{
    t_exe   exe_bus;

    init_exe_bus(&exe_bus, env);
    exec_heredocs(&exe_bus);
	traverse_ast_to_exec(s, &exe_bus);
}  

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

int    traverse_ast_to_exec(t_ast *s, t_exe *b)
{
    int builtin;

    builtin = 0;
    if (s->tag == COMMAND)
	{
		for (int i = 0; i < s->command->size; i++)
		{
            builtin = which_builtin(s->command->args[0]);
            if (builtin)
                exec_builtin(s, b->env);
            else
                exec_bin(s, b->env);
		}
	}
    else if (s->tag == SUBSHELL)
        g_exit = minishell(s->subshell_cmd, b->env);
    else
    {
        if (!b->log_op || (b->log_op == AND && g_exit == 0) || \
            (b->log_op == OR && g_exit == 1))
        {
            if (s->left)
		        g_exit = traverse_ast_to_exec(s->left, b);
        }
        b->log_op = s->op; // assign / update log_op before going right
        if ((b->log_op == AND && g_exit == 0) || \
            (b->log_op == OR && g_exit == 1))
        {
            if (s->right)
		        g_exit = traverse_ast_to_exec(s->right, b);
        }
        // count pipes
        if (s->op == PIPE)
            ;
    }
	if (s->left)
		traverse_ast_to_exec(s->left, b);
	if (s->right)
		traverse_ast_to_exec(s->right, b);
}

void    exec_builtin(t_ast *s, t_list **env)
{
    	t_list	*tmp;
        enum e_bltn builtin_macros;

    	tmp = s->command->ins;
		while (tmp->next)
			tmp = tmp->next;
		tmp = s->command->outs;
		while (tmp->next)
			tmp = tmp->next;
}

void    exec_bin(t_ast *ast, t_list **env)
{
    ;
}
