#include "../../includes/minishell.h"

/*
ppl_cmd_count = 1 bc we traverse the ast recursively and if s->tag == PIPE, cmd_count++
i = -1 bc that's a ++i type counter. To reset it intelligently or to add another one?
*/
static void init_exe_bus(t_exe *exe_bus, t_ast *s, t_list **env)
{
    exe_bus->s = s;
    exe_bus->env = env;
    exe_bus->i = -1;
    exe_bus->hd_count = 0;
    exe_bus->hd_fds = NULL;
    exe_bus->is_pipeline = 0;
    exe_bus->ppl_cmd_count = 1;
    exe_bus->pp_fds[0][0] = 0;
    exe_bus->pp_fds[0][1] = 0;
    exe_bus->pp_fds[1][0] = 0;
    exe_bus->pp_fds[1][1] = 0;
    exe_bus->smpl_cmd_pid = -1;
    exe_bus->ppl_pids = NULL;
    exe_bus->smpl_wstatus = -1;
    exe_bus->ppl_wstatuses = NULL;
    exe_bus->my_paths = NULL;
    exe_bus->execve_path = NULL;
    exe_bus->execve_argv = NULL;
    exe_bus->execve_envp = NULL;
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