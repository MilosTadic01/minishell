#include "../../includes/minishell.h"

void	init_subshell_dos(t_exe *exe_bus)
{
	int	i;

	i = 0;
	exe_bus->subshell_do[i] = 1;
	while (++i < MAX_GOS)
		exe_bus->subshell_do[i] = 0;
}

/*
ppl_cmd_count = 1 bc we traverse the ast recursively and
if s->tag == PIPE, cmd_count++. i = -1 bc that's a ++i type counter.
To reset it intelligently or to add another one? I guess
we're reusing the i, which in hindsight I've come to regret.
*/
static void	init_exe_bus(t_exe *exe_bus, t_ast *s, t_list **env)
{
	exe_bus->s = s;
	exe_bus->env = env;
	exe_bus->i = -1;
	exe_bus->hd_count = 0;
	exe_bus->hd_idx = 0;
	exe_bus->hd_fds = NULL;
	exe_bus->fd_redir_in = -1;
	exe_bus->fd_redir_out = -1;
	exe_bus->is_pipeline = 0;
	exe_bus->subshell_lvl = 0;
	exe_bus->ppl_cmd_count = 0;
	init_subshell_dos(exe_bus);
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

int	exec(t_ast *s, char *subcmd, t_exe *b, t_list **env)
{
	t_exe	exe_bus;

	if (!s || !env || !(*env))
	{
		ft_putstr_fd("minishell: exec: uninitialized args", STDERR_FILENO);
		return (ERROR);
	}
	if (b == NULL)
	{
		init_exe_bus(&exe_bus, s, env);
		if (!subcmd)
		{
			if (exec_heredocs(&exe_bus))
				return (PARSING_ERROR);
		}
		traverse_ast_to_exec(s, &exe_bus);
		free_heredocs(&exe_bus);
	}
	else
		traverse_ast_to_exec(s, b);
	return (SUCCESS);
}
