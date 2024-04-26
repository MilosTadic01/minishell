/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:08:20 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/24 17:22:40 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_ast(t_ast *s)
{
	int	idx;

	if (s->tag == COMMAND)
	{
		idx = 0;
		while (idx < s->command->size)
			free(s->command->args[idx++]);
		free(s->command->args);
		free_item_list(&s->command->ins);
		free_item_list(&s->command->outs);
		free(s->command);
	}
	if (s->left)
		free_ast(s->left);
	if (s->right)
		free_ast(s->right);
	free(s);
}

void	free_item_list(t_list **lst)
{
	t_list	*tmp;
	t_list	*node;

	tmp = *lst;
	while (tmp)
	{
		node = tmp;
		tmp = tmp->next;
		free(node->as_item->filename);
		free(node->as_item);
		free(node);
	}
}