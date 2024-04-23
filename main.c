/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:23:38 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/22 16:37:19 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void print_ast(t_ast *s);

int main(void)
{
	char *i;
	t_ast *ast;
	i = malloc(100);
	fgets(i, 100, stdin);
	i = ft_strtrim(i, " ");
	ast = parse(i);
	print_ast(ast);
	return (0);
}

static void print_ast(t_ast *s)
{
	if (s->tag == COMMAND)
		printf("COMMAND\n");
	else
	{
		printf("BINOP ");
		if (s->op == PIPE)
			printf("PIPE\n");
		if (s->op == AND)
			printf("AND\n");
		if (s->op == OR)
			printf("OR\n");
	}
	for (int i = 0; i < s->command->size; i++)
	{
		printf("%s\n", s->command->args[i]);
	}
	while (s->command->ins)
	{
		printf("input redirections %d to: %s\n", s->command->ins->as_item->type, s->command->ins->as_item->filename);
		s->command->ins = s->command->ins->next;
	}
	while (s->command->outs)
	{
		printf("output redirections %d to: %s\n", s->command->outs->as_item->type, s->command->outs->as_item->filename);
		s->command->outs = s->command->outs->next;
	}
	if (s->left)
		print_ast(s->left);
	if (s->right)
		print_ast(s->right);
}