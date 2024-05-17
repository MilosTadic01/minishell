/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_branches.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:16:26 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/16 14:44:36 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_redir_item	*new_item(int type, char *filename)
{
	t_redir_item	*item;

	item = malloc(sizeof(t_redir_item));
	if (!item)
		return (NULL);
	item->type = type;
	item->filename = filename;
	return (item);
}

t_ast	*new_binop(int op, t_ast **left, t_ast **right)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->op = op;
	ast->tag = BINOP;
	ast->left = *left;
	ast->right = *right;
	ast->subshell_cmd = NULL;
	return (ast);
}

t_ast	*new_command(void)
{
	t_ast		*ast;

	ast = malloc(sizeof(t_ast));
	ast->command = malloc(sizeof(t_command));
	if (!ast || !ast->command)
		return (NULL);
	ast->tag = COMMAND;
	ast->left = NULL;
	ast->right = NULL;
	ast->command->args = NULL;
	ast->command->size = 0;
	ast->command->ins = NULL;
	ast->command->outs = NULL;
	ast->subshell_cmd = NULL;
	return (ast);
}

t_ast	*new_subshell(char *value)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->tag = SUBSHELL;
	ast->subshell_cmd = value;
	ast->op = -1;
	ast->command = NULL;
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}

t_ast	*new_recursive_call(char *value)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->tag = RECCALL;
	ast->subshell_cmd = value;
	ast->op = -1;
	ast->command = NULL;
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}
