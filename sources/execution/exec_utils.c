/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:23:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/17 19:35:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// *strarr = NULL; omitted. This was causing "invalid write of size 8"
void	free_strarr(char **strarr)
{
	int	i;

	i = -1;
	while (strarr[++i])
		free(strarr[i]);
	free(strarr);
}

void	fork_one_for_simple_cmd(t_exe *b)
{
	b->smpl_cmd_pid = fork();
	if (b->smpl_cmd_pid < 0)
	{
		perror("fork");
		free_strarr(b->execve_argv);
		b->execve_argv = NULL;
		free_strarr(b->execve_envp);
		b->execve_envp = NULL;
	}
}

void	fork_one_in_ppl(t_exe *b)
{
	b->ppl_pids[b->i] = fork();
	if (b->ppl_pids[b->i] < 0)
	{
		perror("fork");
		free_strarr(b->execve_argv);
		b->execve_argv = NULL;
		free_strarr(b->execve_envp);
		b->execve_envp = NULL;
	}
}

static void	free_the_distinct_path_and_argv(t_exe *b)
{
	if (b->execve_path)
	{
		free(b->execve_path);
		b->execve_path = NULL;
	}
	if (b->execve_argv)
	{
		free_strarr(b->execve_argv);
		b->execve_path = NULL;
	}
}

void	free_n_error_n_exit(char *errprefix, t_exe *b)
{
	if (errprefix && !b->execve_path)
		errno = ENOENT;
	if (errprefix)
		perror(errprefix);
	if (b->execve_path && b->execve_argv && b->execve_path == b->execve_argv[0])
	{
		free(b->execve_path);
		b->execve_path = NULL;
		b->execve_path = NULL;
	}
	else
		free_the_distinct_path_and_argv(b);
	if (b->execve_envp)
	{
		free_strarr(b->execve_envp);
		b->execve_envp = NULL;
	}
	if (b->my_paths)
	{
		free_strarr(b->my_paths);
		b->my_paths = NULL;
	}
	exit(b->exit_st);
}
