/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:44:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/18 21:11:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec(t_ast *s, char *subcmd, t_exe *b)
{
	if (!s || !b || !(b->env))
	{
		ft_putstr_fd("minishell: exec: uninitialized args", STDERR_FILENO);
		return (ERROR);
	}
	if (b->heredocs_need_execution && !subcmd)
	{
		b->heredocs_need_execution = 0;
		if (exec_heredocs(b))
			return (PARSING_ERROR);
		traverse_ast_to_exec(s, b);
		free_heredocs(b);
	}
	else
		traverse_ast_to_exec(s, b);
	return (SUCCESS);
}
