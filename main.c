/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:23:38 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/25 11:27:16 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void print_ast(t_ast *s);

int main()
{
	char *line;
	char	*copy;
	t_ast *ast;
	//char **my_env;

	//my_env = init_env(envp);
	//while (1)
	//{
		line = readline("minishell> ");
		copy = line;
		line = ft_strtrim(copy, " ");
		free(copy);
		ast = parse(line);
		print_ast(ast);
		add_history(line);
		free(line);
		free_ast(ast);
		// free;
	//}
	return (0);
}

static void print_ast(t_ast *s)
{
	t_list	*tmp;

	if (s->tag == COMMAND)
	{
		printf("COMMAND\n");
		for (int i = 0; i < s->command->size; i++)
		{
			printf("%s\n", s->command->args[i]);
		}
		tmp = s->command->ins;
		while (tmp)
		{
			printf("input redirections %d to: %s\n", tmp->as_item->type, tmp->as_item->filename);
			tmp = tmp->next;
		}
		tmp = s->command->outs;
		while (tmp)
		{
			printf("output redirections %d to: %s\n",  tmp->as_item->type, tmp->as_item->filename);
			tmp = tmp->next;
		}
	}
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
	if (s->left)
		print_ast(s->left);
	if (s->right)
		print_ast(s->right);
}