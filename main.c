/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:23:38 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/03 13:04:53 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// static void print_ast(t_ast *s);
int g_exit;

int main(int argc, char **argv, char **envp)
{
	t_list				*my_env;

	(void)argc;
	(void)argv;
	g_exit = 0;
	my_env = init_env(envp);
	minishell(NULL, &my_env);
	ft_lstclear(&my_env);
	return (0);
}

int	minishell(char *cmd, t_list **my_env)
{
	receive_signals();
	while (1)
	{
		prompt(cmd, my_env);
	}
}

void	prompt(char *cmd, t_list **my_env)
{
	char				*line;
	char				*copy;
	t_ast				*ast;

	if (!cmd)
		line = readline("minishell> ");
	else
		line = cmd;
	if (!line)
		exit(g_exit);
	copy = line;
	line = ft_strtrim(copy, " ");
	free(copy);
	ast = parse(line, my_env);
	// print_ast(ast);
	exec(ast, my_env);
	add_history(line);
	free(line);
	free_ast(ast);
}

// static void print_ast(t_ast *s)
// {
// 	t_list	*tmp;

// 	if (s->tag == COMMAND)
// 	{
// 		printf("COMMAND\n");
// 		for (int i = 0; i < s->command->size; i++)
// 		{
// 			printf("%s\n", s->command->args[i]);
// 		}
// 		tmp = s->command->ins;
// 		while (tmp)
// 		{
// 			printf("input redirections %d to: %s\n", tmp->as_item->type, tmp->as_item->filename);
// 			tmp = tmp->next;
// 		}
// 		tmp = s->command->outs;
// 		while (tmp)
// 		{
// 			printf("output redirections %d to: %s\n",  tmp->as_item->type, tmp->as_item->filename);
// 			tmp = tmp->next;
// 		}
// 	}
// 	else if (s->tag == SUBSHELL)
// 	{
// 		printf("SUBSHELL\n");
// 		printf("%s\n", s->subshell_cmd);
// 	}
// 	else
// 	{
// 		if (s->op == PIPE)
// 			printf("PIPE\n");
// 		if (s->op == AND)
// 			printf("AND\n");
// 		if (s->op == OR)
// 			printf("OR\n");
// 	}
// 	if (s->left)
// 	{
// 		printf("PRINTING LEFT BRANCH:\n");
// 		print_ast(s->left);
// 	}
// 	else
// 		printf("\n");
// 	if (s->right)
// 	{
// 		printf("PRINTING RIGHT BRANCH:\n");
// 		print_ast(s->right);
// 	}
// 	else
// 		printf("\n");
// }