/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_branches.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:16:26 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/22 14:31:18 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	ast->command = malloc(sizeof(t_command));
	if (!ast || !ast->command)
		return (NULL);
	ast->op = op;
	ast->tag = BINOP;
	ast->left = *left;
	ast->right = *right;
	ast->command->size = 0;
	ast->command->ins = NULL;
	ast->command->outs = NULL;
	return (ast);
}

t_ast	*new_command(void)
{
	t_ast		*new_ast;

	new_ast = malloc(sizeof(t_ast));
	new_ast->command = malloc(sizeof(t_command));
	if (!new_ast || !new_ast->command)
		return (NULL);
	new_ast->op = 0;
	new_ast->tag = COMMAND;
	new_ast->left = NULL;
	new_ast->right = NULL;
	new_ast->command->size = 0;
	new_ast->command->ins = malloc(sizeof(t_list));
	new_ast->command->outs = malloc(sizeof(t_list));
	if (!new_ast->command->ins || !new_ast->command->outs)
		return (NULL);
	new_ast->command->ins = NULL;
	new_ast->command->outs = NULL;
	return (new_ast);
}
