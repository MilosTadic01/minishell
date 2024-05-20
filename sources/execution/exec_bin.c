/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:23:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/20 17:30:07 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_bin_in_pipeline(t_ast *s, t_exe *b)
{
	++(b->i);
	reuse_pipe_in_parent(b);
	fork_one_in_ppl(b);
	if (b->ppl_pids[b->i] == 0)
	{
		prep_execve_args(s, b);
		lay_child_pipes(b);
		if (!b->execve_argv || !b->execve_envp
			|| slap_on_redirs_in_child(s, b) == EXIT_FAILURE)
			free_n_error_n_exit(NULL, b);
		execve(b->execve_path, b->execve_argv, b->execve_envp);
		free_n_error_n_exit(b->execve_argv[0], b);
	}
	else
		clean_up_after_redirs_in_parent(b);
}

static void	exec_a_simple_bin(t_ast *s, t_exe *b)
{
	fork_one_for_simple_cmd(b);
	if (b->smpl_cmd_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		prep_execve_args(s, b);
		if (!b->execve_argv || !b->execve_envp
			|| slap_on_redirs_in_child(s, b) == EXIT_FAILURE)
			free_n_error_n_exit(NULL, b);
		execve(b->execve_path, b->execve_argv, b->execve_envp);
		free_n_error_n_exit(b->execve_argv[0], b);
	}
	else
	{
		clean_up_after_redirs_in_parent(b);
		waitpid(b->smpl_cmd_pid, &b->smpl_wstatus, 0);
		if (WIFEXITED(b->smpl_wstatus))
			b->exit_st = WEXITSTATUS(b->smpl_wstatus);
		else if (WIFSIGNALED(b->smpl_wstatus))
			g_exit = 128 + WTERMSIG(b->smpl_wstatus);
		else
			b->exit_st = b->smpl_wstatus;
	}
}

// obsolete at bottom:
// 		receive_signals_interactive();
// 		g_exit = errno;
// 		return (g_exit);
void	exec_bin(t_ast *s, t_exe *b)
{
	set_up_redirs(s, b);
	if (b->is_pipeline)
		exec_bin_in_pipeline(s, b);
	else
		exec_a_simple_bin(s, b);
}
