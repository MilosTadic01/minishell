/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:34:04 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/11 13:05:23 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void free_string(char **str_arr, int size);

struct s_statement	*parse_statement(t_list **token_list)
{
	struct s_statement	*ast;
	struct s_statement	*rest;

	//printf("before ast %s\n", (*token_list)->as_token->value);
	ast = parse_command(token_list);
	//printf("after ast %s\n", (*token_list)->as_token->value);
	if (!(*token_list))
		return (ast);
	if ((*token_list)->as_token->token_type == PIPE)
	{
		(*token_list) = (*token_list)->next;
		rest = parse_statement(token_list);
		ast = new_binop(PIPE, &ast, &rest);
	}
	return (ast);
}

struct s_statement	*new_binop(int op, struct s_statement **left, struct s_statement **right)
{
	struct s_statement	*ast;

	ast = malloc(sizeof(struct s_statement));
	ast->command = malloc(sizeof(struct s_command));
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

struct s_statement	*parse_command(t_list **token_list)
{
	struct s_statement	*ast;
	t_list				*current;
	t_list				*new_node;
	struct s_command 	*c;
	t_redir_item		*item;
	int 				type;

	ast = malloc(sizeof(struct s_statement));
	c = malloc(sizeof(struct s_command));
	if (!ast || !c)
		return (NULL);
	if (!(*token_list))
		return (ast);
	ast->left = NULL;
	ast->right = NULL;
	c->size = 0;
	c->args = NULL;
	c->outs = NULL;
	c->ins = NULL;
	current = (*token_list);
	while (current && current->as_token->token_type != PIPE)
	{
		type = current->as_token->token_type;
		if ((type == REDIRECT_IN || type == REDIRECT_IN_IN || type == REDIRECT_OUT
			|| type == REDIRECT_OUT_OUT))
		{
			item = malloc(sizeof(t_redir_item));
			if (!item)
				return (NULL);
			item->type = type;
			if (!current->next || current->next->as_token->token_type != LITERAL)
				item->filename = NULL;
			else
			{
				current = current->next;
				item->filename = ft_strdup(current->as_token->value);
			}
			new_node = ft_lstnew(&(t_type){.as_item = item}, AS_ITEM);
			if (type == REDIRECT_IN || type == REDIRECT_IN_IN)
				ft_lstadd_back(&c->ins, new_node);
			else
				ft_lstadd_back(&c->outs, new_node);
			current = current->next;
		}
		else
		{
			c->args = ft_strappend(c->args, current->as_token->value, c->size);
			c->size++;
			current = current->next;
		}
	}
	ast->tag = COMMAND;
	ast->command = c;
	*(token_list) = current;
	return (ast);
}

t_list	*pop_token(t_list **token_list)
{
	t_list	*current;

	if (*token_list)
	{
		current = *token_list;
		*token_list = (*token_list)->next;
		return (current);
	}
	return (NULL);
}

t_list	*peek_token(t_list *token_list)
{
	t_list	*next;

	next = token_list->next;
	return (next);
}

char	**append_token(char **command, t_list *next, int size)
{
	char	*tmp;
	char	**new_command;

	tmp = next->as_token->value;
	new_command = ft_strappend(command, tmp, size);
	free_string(command, size);
	if (!new_command)
		return (NULL);
	return (new_command);
}

int	is_literal(t_list *token_list)
{
	if (token_list->as_token->token_type == LITERAL)
		return (1);
	return (0);
}

static void free_string(char **str_arr, int size)
{
	int idx;

	idx = 0;
	while (idx < size)
	{
		free(str_arr[idx]);
		idx++;
	}
}
