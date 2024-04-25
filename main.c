/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:23:38 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/25 12:04:17 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void print_ast(t_ast *s);
t_list  *init_env(char **envp);

int main(int argc, char **argv, char **envp)
{
	char *line;
	char	*copy;
	t_ast *ast;
	t_list *my_env;
	t_exe   exe_bus;

	(void)argc;
	(void)argv;
	my_env = init_env(envp);
	//while (1)
	//{
		line = readline("minishell> ");
		copy = line;
		line = ft_strtrim(copy, " ");
		free(copy);
		ast = parse(line);
		
		//print_ast(ast);
		add_history(line);
		exec(exe_bus);
		free(line);
		free_ast(ast);
		//free;
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

/*t_list	*test(char **str, int size)
{
	int	i;
	t_type	tmp;
	t_list	*lst;

	i = 0;
	while (i < size)
	{
		tmp = (t_type){.as_str = str[i]};
		ft_lstadd_back(&lst, ft_lstnew(&tmp, AS_STR));
	}
}*/

t_list  *init_env(char **envp)
{
    t_list  *my_env;
    t_type  tmp;
    int     i;

    i = -1;
	my_env = NULL;
    while(envp[++i])
        ;
    while(--i >= 0)
    {
        tmp = (t_type){.as_str = envp[i]};
        ft_lstadd_back(&my_env, ft_lstnew(&tmp, AS_STR));
    }
    while(my_env)
    {
        printf("%s\n", my_env->as_str);
        my_env = my_env->next;
    }
    return (my_env);
}