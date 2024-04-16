/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:28:45 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/11 14:37:40 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static void	print_token_list(t_list *list);
static void	print_ast(struct s_statement *s);

int main(void)
{
	char	*input;
	t_list	*list;
	struct s_statement *s;

	input = malloc(100);
	fgets(input, 100, stdin);
	input = ft_strtrim(input, " ");
	list = lex_input(input);
	print_token_list(list);
	s = parse_statement(&list);
	print_ast(s);
	/*printf("%d\n", s->tag);
	for (int i = 0; i < s->command->size; i++)
			printf("%s\n", s->command->args[i]);
	if (s->left)
	{
		for (int i = 0; i < s->left->command->size; i++)
			printf("%s\n", s->left->command->args[i]);
	}
	printf("PIPE\n");
	if (s->right)
	{
		for (int i = 0; i < s->right->command->size; i++)
			printf("%s\n", s->right->command->args[i]);
	}
	while (s->command->ins)
	{
		printf("infile %d: %s\n", s->command->ins->as_item->type,  s->command->ins->as_item->filename);
		s->command->ins = s->command->ins->next;
	}
	while (s->command->outs)
	{
		printf("outfile %d: %s\n", s->command->outs->as_item->type,  s->command->outs->as_item->filename);
		s->command->outs = s->command->outs->next;
	}*/
	return (0);
}

static void	print_token_list(t_list *list)
{
	t_list	*copy;

	copy = list;
	while (copy)
	{
		printf("(value: %s; ", copy->as_token->value);
		if (copy->next)
			printf("type: %d) -> ", copy->as_token->token_type);
		else
			printf("type: %d)\n", copy->as_token->token_type);
		copy = copy->next;
	}

}

static void	print_ast(struct s_statement *s)
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
		printf("input redirections %d: %s\n", s->command->ins->as_item->type,  s->command->ins->as_item->filename);
		s->command->ins = s->command->ins->next;
	}
	while (s->command->outs)
	{
		printf("output redirections %d: %s\n", s->command->outs->as_item->type,  s->command->outs->as_item->filename);
		s->command->outs = s->command->outs->next;
	}
	if (s->left)
		print_ast(s->left);
	if (s->right)
		print_ast(s->right);
}