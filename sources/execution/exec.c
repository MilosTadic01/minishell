#include "../../includes/minishell.h"

static void init_exe_bus(t_exe *exe_bus, t_ast *s, t_list *env)
{
    exe_bus->s = s;
    exe_bus->env = env;
    exe_bus->heredoc_fds = NULL;
    exe_bus->heredoc_count = 0;
}

static void open_files_for_heredocs(t_exe *exe_bus)
{
    int i;

    i = 0;
    while (i < exe_bus->heredoc_count)
        exe_bus->heredoc_fds[i] = open("/tmp/file", O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void    exec_heredocs(t_exe *exe_bus)
{
    t_list	*tmp;

    tmp = exe_bus->s->command->ins;
    // count heredocs
    while (tmp)
    {
        if (tmp->as_item->type == REDIRECT_IN_IN)
            exe_bus->heredoc_count++;
        tmp = tmp->next;
    }
    // malloc
    exe_bus->heredoc_fds = malloc(exe_bus->heredoc_count * sizeof(int));
    // open files
    open_files_for_heredocs(exe_bus);
    // run prompts
    while (tmp)
    {
        exe_bus->heredoc_fds[0] = readline(">");
        tmp = tmp->next;
    }
}

void    exec(t_ast *s, t_list *env)
{
    t_exe   exe_bus;

    init_exe_bus(&exe_bus, s, env);
    exec_heredocs(&exe_bus);
	traverse_ast_to_exec(s, exe_bus);
}

void    traverse_ast_to_exec(t_ast *s, t_exe b)
{
    if (s->tag == COMMAND)
	{
		// printf("COMMAND\n");
		for (int i = 0; i < s->command->size; i++)
		{
			// printf("%s\n", s->command->args[i]);
            if (is_builtin(s->command->args[0]))
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
