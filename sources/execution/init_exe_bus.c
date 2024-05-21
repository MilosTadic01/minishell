/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exe_bus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:23:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/18 19:35:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_subshell_dos(t_exe *exe_bus)
{
	int	i;

	i = 0;
	exe_bus->subshell_do[i] = 1;
	while (++i < MAX_GOS)
		exe_bus->subshell_do[i] = 0;
}

static void	init_pipe_fds(t_exe *exe_bus)
{
	exe_bus->pp_fds[0][0] = 0;
	exe_bus->pp_fds[0][1] = 0;
	exe_bus->pp_fds[1][0] = 0;
	exe_bus->pp_fds[1][1] = 0;
}

void	pre_ast_init_exe_bus(t_exe *exe_bus, t_list **my_env)
{
	exe_bus->exit_st = 0;
	exe_bus->s = NULL;
	exe_bus->env = my_env;
}

/*
ppl_cmd_count = 1 bc we traverse the ast recursively and
if s->tag == PIPE, cmd_count++. i = -1 bc that's a ++i type counter.
To reset it intelligently or to add another one? I guess
we're reusing the i, which in hindsight I've come to regret.
*/
void	big_init_exe_bus_with_ast(t_ast *s, t_exe *exe_bus)
{
	exe_bus->s = s;
	exe_bus->heredocs_need_execution = 1;
	exe_bus->i = -1;
	exe_bus->hd_count = 0;
	exe_bus->hd_idx = 0;
	exe_bus->hd_fds = NULL;
	exe_bus->hd_delimiters = NULL;
	exe_bus->fd_redir_in = -1;
	exe_bus->fd_redir_out = -1;
	exe_bus->is_pipeline = 0;
	exe_bus->subshell_lvl = 0;
	exe_bus->ppl_cmd_count = 0;
	init_subshell_dos(exe_bus);
	init_pipe_fds(exe_bus);
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
