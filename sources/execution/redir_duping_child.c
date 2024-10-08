/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_duping_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:23:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/18 19:35:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	dup2_and_close_redir_out(t_exe *b)
{
	if (b->fd_redir_out > -1 && dup2(b->fd_redir_out, STDOUT_FILENO) < 0)
	{
		perror("dup2 for redir_out");
		return (EXIT_FAILURE);
	}
	if (b->fd_redir_out > -1 && close(b->fd_redir_out) < 0)
	{
		perror("close fd_redir_out");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	dup2_and_close_redir_in(t_exe *b)
{
	if (b->fd_redir_in > -1 && dup2(b->fd_redir_in, STDIN_FILENO) < 0)
	{
		perror("dup2 for redir_in");
		return (EXIT_FAILURE);
	}
	if (b->fd_redir_in > -1 && close(b->fd_redir_in) < 0)
	{
		perror("close fd_redir_in");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	slap_on_redirs_in_child(t_ast *s, t_exe *b)
{
	if (s->command->ins && (!s->command->args || b->fd_redir_in == -1))
	{
		close(STDIN_FILENO);
		b->exit_st = 1;
		return (EXIT_FAILURE);
	}
	if (s->command->outs && b->fd_redir_out == -1)
	{
		b->exit_st = 1;
		return (EXIT_FAILURE);
	}
	if (dup2_and_close_redir_in(b) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (dup2_and_close_redir_out(b) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
