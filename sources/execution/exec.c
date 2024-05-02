#include "../../includes/minishell.h"

static void init_exe_bus(t_exe *exe_bus, t_ast *s, t_list *env)
{
    exe_bus->s = s;
    exe_bus->env = env;
    exe_bus->heredoc_fds = NULL;
    exe_bus->heredoc_count = 0;
    exe_bus->pids = NULL;
}

void    exec(t_ast *s, t_list *env)
{
    t_exe   exe_bus;

    init_exe_bus(&exe_bus, s, env);
    exec_heredocs(&exe_bus);
	traverse_ast_to_exec(s, exe_bus);
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

void    traverse_ast_to_exec(t_ast *s, t_exe b)
{
    int builtin;

    builtin = 0;
    if (s->tag == COMMAND)
	{
		// printf("COMMAND\n");
		for (int i = 0; i < s->command->size; i++)
		{
			// printf("%s\n", s->command->args[i]);
            builtin = which_builtin(s->command->args[0]);
            if (builtin)
                exec_builtin(s, &env);
            else
                exec_bin(s, &env);
		}
	}
	// else
	// {
	// 	// printf("BINOP ");
	// 	// if (s->op == PIPE)
	// 	// 	printf("PIPE\n");
	// }
	if (s->left)
		traverse_ast_to_exec(s->left, b);
	if (s->right)
		traverse_ast_to_exec(s->right, b);
}

void    exec_builtin(t_ast *s, t_list **env)
{
    	t_list	*tmp;
        e_bltin builtin_macros;

    	tmp = s->command->ins;
		while (tmp->next)
		{
			// printf("input redirections %d to: %s\n", tmp->as_item->type, tmp->as_item->filename);
			tmp = tmp->next;
		}
		tmp = s->command->outs;
		while (tmp->next)
		{
			// printf("output redirections %d to: %s\n",  tmp->as_item->type, tmp->as_item->filename);
			tmp = tmp->next;
		}
}

void    exec_bin(t_ast *ast, t_list **env)
{}
