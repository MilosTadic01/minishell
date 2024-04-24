/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_branches.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:16:26 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/24 13:41:48 by dzubkova         ###   ########.fr       */
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
	return (ast);
}

t_ast	*new_command(void)
{
	t_ast		*new_ast;

	new_ast = malloc(sizeof(t_ast));
	new_ast->command = malloc(sizeof(t_command));
	if (!new_ast || !new_ast->command)
		return (NULL);
	new_ast->tag = COMMAND;
	new_ast->left = NULL;
	new_ast->right = NULL;
	new_ast->command->args = NULL;
	new_ast->command->size = 0;
	new_ast->command->ins = NULL;
	new_ast->command->outs = NULL;
	return (new_ast);
}
