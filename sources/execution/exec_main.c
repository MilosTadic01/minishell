/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:44:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/20 17:03:48 by dzubkova         ###   ########.fr       */
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
	if (!subcmd)
	{
		big_init_exe_bus_with_ast(s, b);
		if (exec_heredocs(b))
			return (PARSING_ERROR);
		traverse_ast_to_exec(s, b);
		free_heredocs(b);
	}
	else
		traverse_ast_to_exec(s, b);
	return (SUCCESS);
}
