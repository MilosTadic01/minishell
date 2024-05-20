/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:13:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/19 19:32:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
obsolete conditional checks for update_pipe_info
if (s->tag == COMMAND)
if (s->tag == COMMAND || s->tag == RECCALL)
and
else if (s->tag == SUBSHELL || s->tag == RECCALL)
*/
static void	update_pipe_info(t_ast *s, t_exe *b)
{
	t_ast	*reccall_ast;

	reccall_ast = NULL;
	b->is_pipeline = 1;
	if (s->tag == COMMAND || (s->tag == BINOP && s->op != PIPE))
		b->ppl_cmd_count++;
	else if (s->tag == BINOP && s->op == PIPE)
	{
		if (s->left)
			update_pipe_info(s->left, b);
		if (s->right)
			update_pipe_info(s->right, b);
	}
	else if (s->tag == SUBSHELL)
	{
		reccall_ast = parse(s->subshell_cmd, b);
		if (!reccall_ast)
			ft_putstr_fd("pipe counter: failed to parse subshell_cmd\n", 2);
		if (reccall_ast)
			update_pipe_info(reccall_ast, b);
		free_ast(reccall_ast);
	}
}

static void	prep_pipes_n_pids(t_exe *b)
{
	b->i = -1;
	b->ppl_pids = (pid_t *)malloc(b->ppl_cmd_count * sizeof(pid_t));
	if (!(b->ppl_pids))
		ft_putstr_fd("ppl_pids: malloc fail\n", 2);
	b->ppl_wstatuses = malloc(b->ppl_cmd_count * sizeof(int));
	if (!(b->ppl_wstatuses))
		ft_putstr_fd("ppl_wstatuses: malloc fail\n", 2);
	if (b->ppl_cmd_count == 2)
	{
		if (pipe(b->pp_fds[0]) < 0)
			ft_putstr_fd("prep_pipes: pipe() fail\n", 2);
		b->pp_fds[1][0] = -1;
		b->pp_fds[1][1] = -1;
	}
	else
	{
		if (pipe(b->pp_fds[0]) < 0 || pipe(b->pp_fds[1]) < 0)
			ft_putstr_fd("prep_pipes: pipe() fail\n", 2);
	}
}

void	set_up_pipeline(t_ast *s, t_exe *b)
{
	update_pipe_info(s, b);
	prep_pipes_n_pids(b);
}

////////////////////////////////////////////////

// void	fork_one(t_exe *b, int i, pid_t *children)
// {
// 	children[i] = fork();
// 	if (children[i] < 0)
// 		; // fail
// }

// void	go_exec(t_exe *b)
// {
// 	int	fds[2][2];
// 	int	i;
// 	pid_t	*children;

// 	prep(b, fds, &children);
// 	// ch_1st_prc(data, fds, children)
// 	i = 0;
// 	while (++i < (b->ppl_cmd_count - 1))
// 	{
// 		if (reuse_pipe(i, b->ppl_cmd_count, fds) < 0)
// 			// fail <- could do this inside 'reuse_pipe'
// 		fork_one(b, i, children);
// 		if (!children[i])
// 		{
// 			// ch_mid_prc(data, fds, i)
// 			// fail
// 		}
// 	}
// 	fork_one(b, i, children);
// 	if (!children[i])
// 		// ch_last_prc
// 	pipe_closer(i, fds);
// 	go_wait(b, children);
// 	free(children);
// }