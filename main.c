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

static void print_ast(t_ast *s);
t_list  *init_env(char **envp);

int main(int argc, char **argv, char **envp)
{
	t_list				*my_env;

	(void)argc;
	(void)argv;
	(void)envp;
	// my_env = init_env(envp);
	//ft_printenv(my_env);
	// ft_putstr_fd(ft_getenv(my_env, "SHLVL"), STDOUT_FILENO);
	// ft_putstr_fd("\n", STDOUT_FILENO);
	receive_signals();
	while (1)
	{
		prompt();
		//free;
	}
	ft_lstclear(&my_env);
	return (0);
}

void	prompt(void)
{
	char				*line;
	char				*copy;
	t_ast				*ast;

	line = readline("minishell> ");
	if (!line)
		exit(errno);
	copy = line;
	line = ft_strtrim(copy, " ");
	free(copy);
	ast = parse(line);
	print_ast(ast);
	add_history(line);
	free(line);
	free_ast(ast);
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
	else if (s->tag == SUBSHELL)
	{
		printf("SUBSHELL\n");
		printf("%s\n", s->subshell_cmd);
	}
	else
	{
		if (s->op == PIPE)
			printf("PIPE\n");
		if (s->op == AND)
			printf("AND\n");
		if (s->op == OR)
			printf("OR\n");
	}
	if (s->left)
	{
		printf("PRINTING LEFT BRANCH:\n");
		print_ast(s->left);
	}
	else
		printf("\n");
	if (s->right)
	{
		printf("PRINTING RIGHT BRANCH:\n");
		print_ast(s->right);
	}
	else
		printf("\n");
}

// t_list  *init_env(char **envp)
// {
//     t_list  *my_env;
//     t_type  tmp;
//     int     i;

//     i = -1;
// 	my_env = NULL;
//     while(envp[++i])
//         ;
//     while(--i >= 0)
//     {
//         tmp = (t_type){.as_str = envp[i]};
//         ft_lstadd_back(&my_env, ft_lstnew(&tmp, AS_STR));
//     }
//     while(my_env)
//     {
//         printf("%s\n", my_env->as_str);
//         my_env = my_env->next;
//     }
//     return (my_env);
// }