/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:23:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/18 19:35:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_up_after_redirs_in_parent(t_exe *b)
{
	if (b->fd_redir_in > -1 && close(b->fd_redir_in) < 0)
		perror("close fail of fd_redir_in in parent");
	b->fd_redir_in = -1;
	if (b->fd_redir_out > -1 && close(b->fd_redir_out) < 0)
		perror("close fail of fd_redir_out in parent");
	b->fd_redir_out = -1;
}
