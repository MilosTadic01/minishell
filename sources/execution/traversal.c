/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traversal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:44:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/18 11:12:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*features bottom of ppl for currently parsed command (if b->is_ppl == 1...)
Furthermore:
1. if (s->op == PIPE...) => count pipes, set is_pipeline to True
2. b->log_op = s->op; assign / update log_op before going right*/

// Why isn't it required like this for bottom of ast?
	// if (b->is_pipeline == 1 && (s->right == NULL || 
	// 		(s->right != NULL && s->right->tag == BINOP && 
	// 		(s->right->op == AND || s->right->op == OR))))
static void	logical_and_pipal_jiujitsu_and_leftright_rec(t_ast *s, t_exe *b)
{
	if (s->op == PIPE && b->is_pipeline == 0 && \
		b->subshell_do[b->subshell_lvl] && \
		((b->log_op == AND && b->exit_st == 0) || \
		(b->log_op == OR && b->exit_st > 0) || b->log_op == 0))
		set_up_pipeline(s, b);
	if (s->left)
		traverse_ast_to_exec(s->left, b);
	b->log_op = s->op;
	if (b->is_pipeline == 1 && s->right != NULL && \
			(s->right->tag == BINOP && \
			(s->right->op == AND || s->right->op == OR)))
		close_pipes_and_wait_and_reset_pipeline(b);
	if (s->right)
		traverse_ast_to_exec(s->right, b);
}

static void	set_subshell_do(t_exe *b)
{
	int	i;

	i = 0;
	while (i < b->subshell_lvl && b->subshell_do[i] == 1)
		i++;
	i--;
	if (i == (b->subshell_lvl - 1) && \
			(!b->log_op || b->log_op == PIPE || \
			(b->log_op == AND && b->exit_st == 0) || \
			(b->log_op == OR && b->exit_st > 0)))
		b->subshell_do[b->subshell_lvl] = 1;
}

static void	increment_subshell_lvl_and_call_rec_minishell(t_ast *s, t_exe *b)
{
	++(b->subshell_lvl);
	set_subshell_do(b);
	minishell(ft_strdup(s->subshell_cmd), b);
	--(b->subshell_lvl);
}

// previous approach: if (!s || !s->command || !s->command->args), return ;
static void	command_exec(t_ast *s, t_exe *b)
{
	int	builtin;

	builtin = 0;
	if (!s || !s->command)
		return ;
	if (b->subshell_do[b->subshell_lvl] && \
		(!b->log_op || (b->log_op == PIPE && b->is_pipeline > 0) || \
		(b->log_op == AND && b->exit_st == 0) || \
		(b->log_op == OR && b->exit_st > 0)))
	{
		if (s->command->args)
			builtin = which_builtin(s->command->args[0]);
		if (builtin)
			exec_builtin(builtin, s, b);
		else
			exec_bin(s, b);
	}
	else
		increment_hd_idx(s, b);
}

/*features bottom of the final pipeline of the cmd_seq (if b->is_ppl == 1...)*/
void	traverse_ast_to_exec(t_ast *s, t_exe *b)
{
	if (s->tag == COMMAND)
		command_exec(s, b);
	else if (s->tag == SUBSHELL)
		increment_subshell_lvl_and_call_rec_minishell(s, b);
	else if (s->tag == RECCALL)
		minishell(ft_strdup(s->subshell_cmd), b);
	else
		logical_and_pipal_jiujitsu_and_leftright_rec(s, b);
	if (b->is_pipeline == 1 && (b->i == b->ppl_cmd_count - 1))
		close_pipes_and_wait_and_reset_pipeline(b);
}
