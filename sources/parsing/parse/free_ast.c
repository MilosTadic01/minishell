/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:08:20 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/17 09:12:39 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_ast(t_ast *s)
{
	int	idx;

	if (!s)
		return ;
	if (s->tag == COMMAND)
	{
		idx = 0;
		while (idx < s->command->size)
			free(s->command->args[idx++]);
		free(s->command->args);
		s->command->args = NULL;
		free_item_list(&s->command->ins);
		free_item_list(&s->command->outs);
		free(s->command);
		s->command = NULL;
	}
	else if (s->tag == SUBSHELL || s->tag == RECCALL)
		free(s->subshell_cmd);
	if (s->left)
		free_ast(s->left);
	if (s->right)
		free_ast(s->right);
	free(s);
	s = NULL;
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

void	free_str(char **str, int size)
{
	int	idx;

	idx = 0;
	while (idx < size)
	{
		free(str[idx]);
		idx++;
	}
	free(str);
}
