/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_outs_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:23:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/18 15:35:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	try_opening_all_outfiles(t_ast *s, t_exe *b)
{
	t_list	*outs_cpy;

	outs_cpy = s->command->outs;
	while (outs_cpy)
	{
		if (outs_cpy->as_item->type == REDIRECT_OUT)
			b->fd_redir_out = open(outs_cpy->as_item->filename, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (outs_cpy->as_item->type == REDIRECT_OUT_OUT)
			b->fd_redir_out = open(outs_cpy->as_item->filename, \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (b->fd_redir_out < 0)
		{
			perror("-minishell: open file for redir_out");
			b->exit_st = 1;
			return (EXIT_FAILURE);
		}
		outs_cpy = outs_cpy->next;
	}
	return (EXIT_SUCCESS);
}
