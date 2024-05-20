/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fu_children.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:23:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/16 19:35:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	if_not_last_ppl_cmd_then_redir_out(t_exe *b)
{
	if (b->pp_fds[b->i % 2][0] > -1)
	{
		if (close(b->pp_fds[b->i % 2][0]) < 0)
			perror("close");
	}
	if (b->pp_fds[b->i % 2][1] > -1)
	{
		dup2(b->pp_fds[b->i % 2][1], STDOUT_FILENO);
		if (close(b->pp_fds[b->i % 2][1]) < 0)
			perror("close");
	}
}

static void	if_not_zeroth_ppl_cmd_then_redir_in(t_exe *b)
{
	if (b->pp_fds[1 - (b->i % 2)][0] > -1)
	{
		dup2(b->pp_fds[1 - (b->i % 2)][0], STDIN_FILENO);
		if (close(b->pp_fds[1 - (b->i % 2)][0]) < 0)
			perror("close");
	}
	if (b->pp_fds[1 - (b->i % 2)][1] > -1)
	{
		if (close(b->pp_fds[1 - (b->i % 2)][1]) < 0)
			perror("close");
	}
}

// if (b->i != b->ppl_cmd_count - 1) :
// if not last ppl_cmd, redir out
// if (b->i != 0) :
// if not 0th ppl_cmd, redir in
// else if (b->i == 0) :
// if 0th ppl_cmd, close the "lead-in" pipe, important for cat | cat | ls
void	lay_child_pipes(t_exe *b)
{
	if (b->i != b->ppl_cmd_count - 1)
		if_not_last_ppl_cmd_then_redir_out(b);
	if (b->i != 0)
		if_not_zeroth_ppl_cmd_then_redir_in(b);
	else if (b->i == 0)
	{
		if (b->pp_fds[1 - (b->i % 2)][0] > -1)
			close(b->pp_fds[1 - (b->i % 2)][0]);
		if (b->pp_fds[1 - (b->i % 2)][1] > -1)
			close(b->pp_fds[1 - (b->i % 2)][1]);
	}
}
