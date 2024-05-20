/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_ins_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:23:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/18 19:35:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	reopen_hd_file_for_reading(t_exe *b, int i)
{
	char	*num;
	char	*path;

	num = ft_itoa(i);
	path = ft_strjoin("/tmp/heredoc", num);
	free(num);
	b->fd_redir_in = open(path, O_RDONLY, 0644);
	free(path);
	if (b->fd_redir_in < 0)
	{
		perror("-minishell: heredoc");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// This was a cool idea but wasn't fitting the purpose
// b->fd_redir_in = open("/dev/null", O_RDONLY);
int	open_and_close_infiles_while_legit(t_ast *s, t_exe *b, int hd_count)
{
	t_list	*ins_cpy;
	int		i;

	i = -1;
	ins_cpy = s->command->ins;
	while (ins_cpy)
	{
		if (ins_cpy->as_item->type == REDIRECT_IN_IN)
			reopen_hd_file_for_reading(b, (b->hd_idx - hd_count + ++i));
		else if (ins_cpy->as_item->type == REDIRECT_IN)
		{
			b->fd_redir_in = open(ins_cpy->as_item->filename, O_RDONLY);
			if (b->fd_redir_in < 0)
			{
				ft_putstr_fd("-minishell: ", 2);
				perror(ins_cpy->as_item->filename);
				return (EXIT_FAILURE);
			}
		}
		if (ins_cpy->next && b->fd_redir_in > -1)
			close(b->fd_redir_in);
		ins_cpy = ins_cpy->next;
	}
	return (EXIT_SUCCESS);
}

int	count_hds_in_this_cmd(t_ast *s)
{
	t_list	*ins_cpy;
	int		hds;

	hds = 0;
	ins_cpy = s->command->ins;
	while (ins_cpy)
	{
		if (ins_cpy->as_item->type == REDIRECT_IN_IN)
			hds++;
		ins_cpy = ins_cpy->next;
	}
	return (hds);
}

static int	are_all_infiles_legit(t_ast *s)
{
	t_list	*ins_cpy;

	ins_cpy = s->command->ins;
	while (ins_cpy)
	{
		if (ins_cpy->as_item->type == REDIRECT_IN)
		{
			if (access(ins_cpy->as_item->filename, R_OK) != 0)
				return (0);
		}
		ins_cpy = ins_cpy->next;
	}
	return (1);
}

void	infile_legitimacy_control(t_ast *s, t_exe *b, int hd_count)
{
	if (!are_all_infiles_legit(s))
	{
		b->hd_idx += hd_count;
		b->fd_redir_in = -1;
		b->exit_st = 1;
	}
}
