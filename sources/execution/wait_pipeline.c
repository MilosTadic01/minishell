/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:02:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/19 11:13:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	go_wait(t_exe *b)
{
	int	i;

	i = -1;
	while (++i < b->ppl_cmd_count)
		waitpid(b->ppl_pids[i], &b->ppl_wstatuses[i], 0);
	if (i > 0)
		b->exit_st = (b->ppl_wstatuses[i - 1] >> 8) & 0xFF;
	free(b->ppl_pids);
	free(b->ppl_wstatuses);
}

// obsolete:
// void	go_wait(t_exe *b)
// {
// 	int	i;
// 	pid_t   *wpid;

// 	i = -1;
// 	wpid = malloc(b->ppl_cmd_count * sizeof(pid_t));
// 	while (++i < b->ppl_cmd_count)
// 	{
// 		// if (b->ppl_pids[b->i] == -1)
//		// currently ignoring this idea, bc in a ppl, builtins are forked for
// 		    continue ;
// 		receive_signals_noninteractive();
// 		wpid[i] = waitpid(b->ppl_pids[i], &b->ppl_wstatuses[i], 0);
// 		waitpid(b->ppl_pids[i], &b->ppl_wstatuses[i], 0);
// 		receive_signals_interactive();
// 		if (wpid[i] < 0)
// 		    ft_putstr_fd("waitpid: error\n", 2);
// 	}
// 	if (i > 0)
// 		b->exit_st = (b->ppl_wstatuses[i - 1] >> 8) & 0xFF;
// 	free(wpid);
// 	free(b->ppl_pids);
// 	free(b->ppl_wstatuses);
// }