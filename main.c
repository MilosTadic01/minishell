/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:23:38 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/21 13:29:43 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//static void print_ast(t_ast *s);
static void	clean_and_run(char **line, t_exe *b);

int	g_exit;

int	main(int argc, char **argv, char **envp)
{
	t_list	*my_env;
	t_exe	exe_bus;

	(void)argc;
	(void)argv;
	g_exit = 0;
	my_env = init_env(envp);
	pre_ast_init_exe_bus(&exe_bus, &my_env);
	minishell(NULL, &exe_bus);
	ft_lstclear(&my_env);
	return (0);
}

void	minishell(char *subcmd, t_exe *b)
{
	if (!subcmd)
	{
		while (1)
			prompt(subcmd, b);
	}
	else
		prompt(subcmd, b);
}

void	prompt(char *subcmd, t_exe *b)
{
	char				*line;
	char				*copy;
	t_ast				*ast;

	receive_signals_interactive();
	if (!subcmd)
		line = readline("minishell> ");
	else
		line = subcmd;
	if (!line)
		exit(b->exit_st);
	receive_signals_noninteractive();
	copy = line;
	line = ft_strtrim(copy, " ");
	free(copy);
	ast = parse(line, b);
	if (!ast)
		return (clean_and_run(&line, b));
	if (*line != 0 && exec(ast, subcmd, b))
		return (clean_and_run(&line, b));
	if (*line != 0)
		add_history(line);
	free(line);
	free_ast(ast);
}

static void	clean_and_run(char **line, t_exe *b)
{
	ft_putendl_fd("Error: bad syntax", STDERR_FILENO);
	b->exit_st = 2;
	add_history(*line);
	free(*line);
	return (minishell(NULL, b));
}

// static void print_ast(t_ast *s)
//  {
//  	t_list	*tmp;

//  	if (s->tag == COMMAND)
//  	{
//  		printf("COMMAND\n");
//  		for (int i = 0; i < s->command->size; i++)
//  		{
//  			printf("%s\n", s->command->args[i]);
//  		}
//  		tmp = s->command->ins;
//  		while (tmp)
//  		{
//  			printf("input redirections %d to: %s\n",
// tmp->as_item->type, tmp->as_item->filename);
//  			tmp = tmp->next;
//  		}
//  		tmp = s->command->outs;
//  		while (tmp)
//  		{
//  			printf("output redirections %d to: %s\n",
// tmp->as_item->type, tmp->as_item->filename);
//  			tmp = tmp->next;
//  		}
//  	}
//  	else if (s->tag == SUBSHELL)
//  	{
//  		printf("SUBSHELL\n");
//  		printf("%s\n", s->subshell_cmd);
//  	}
// 	else if (s->tag == RECCALL)
// 	{
// 		printf("RECCAL\n");
//  		printf("%s\n", s->subshell_cmd);
// 	}
//  	else
//  	{
//  		if (s->op == PIPE)
//  			printf("PIPE\n");
//  		if (s->op == AND)
//  			printf("AND\n");
//  		if (s->op == OR)
//  			printf("OR\n");
//  	}
//  	if (s->left)
//  	{
//  		printf("PRINTING LEFT BRANCH:\n");
//  		print_ast(s->left);
//  	}
//  	else
//  		printf("\n");
//  	if (s->right)
//  	{
//  		printf("PRINTING RIGHT BRANCH:\n");
//  		print_ast(s->right);
//  	}
//  	else
//  		printf("\n");
//  }