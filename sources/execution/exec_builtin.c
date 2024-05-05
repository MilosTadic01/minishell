#include "../../includes/minishell.h"

static int ft_call_builtin(int builtin, t_ast *s, t_exe *b)
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

int    exec_builtin(int builtin, t_ast *s, t_exe *b)
{
    	// t_list	*tmp;

    	// tmp = s->command->ins;
		// while (tmp->next) segfault when no redir
		// 	tmp = tmp->next;
        // // redir in, use tmp
		// tmp = s->command->outs;
		// while (tmp->next)
		// 	tmp = tmp->next; segfault when no redir
        // redir out, use tmp
        return (ft_call_builtin(builtin, s, b));
}