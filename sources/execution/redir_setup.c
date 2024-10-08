/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:23:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/18 17:11:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_up_redir_outs(t_ast *s, t_exe *b)
{
	if (s->command->outs)
	{
		if (try_opening_all_outfiles(s, b) == EXIT_FAILURE)
		{
			b->fd_redir_out = -1;
			b->exit_st = 1;
		}
	}
}

/* hd_idx is immediately increased by hd_count, because we may need to stop
the opening and closing of infiles early if one of them is fd == -1 and we
need the correct hd_idx (more hd_to carry over into the following commands */
// obsolete after += hd_count:
// 		infile_legitimacy_control(s, b, hd_count);
// 		if (infile_legitimacy_control(s, b, hd_count) == EXIT_FAILURE)
//			return ;
static int	set_up_redir_ins(t_ast *s, t_exe *b)
{
	int	hd_count;

	if (s->command->ins)
	{
		hd_count = count_hds_in_this_cmd(s);
		b->hd_idx += hd_count;
		if (open_and_close_infiles_while_legit(s, b, hd_count) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	set_up_redirs(t_ast *s, t_exe *b)
{
	if (!s->command->ins && !s->command->outs)
		return ;
	if (set_up_redir_ins(s, b) == EXIT_FAILURE)
		return ;
	set_up_redir_outs(s, b);
}
