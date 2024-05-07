#include "../../includes/minishell.h"

static void init_exe_bus(t_exe *exe_bus, t_ast *s, t_list **env)
{
    exe_bus->s = s;
    exe_bus->env = env;
    exe_bus->i = -1;
    exe_bus->hd_fds = NULL;
    exe_bus->hd_count = 0;
    exe_bus->is_pipeline = 0;
    exe_bus->cmds_in_ppline = 1;
    exe_bus->pids = NULL;
    exe_bus->log_op = 0;
}

void    exec(t_ast *s, char *subcmd, t_list **env)
{
    t_exe   exe_bus;

    if (!s || !env || !(*env))
    {
        ft_putstr_fd("minishell: exec: uninitialized args", STDERR_FILENO);
        return ;
    }
    init_exe_bus(&exe_bus, s, env);
    if (!subcmd)
        exec_heredocs(&exe_bus);
    traverse_ast_to_exec(s, &exe_bus);
}  

int    exec_bin(t_ast *ast, t_list **env)
{
    (void)ast;
    (void)env;
    return (0);
}