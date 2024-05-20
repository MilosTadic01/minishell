/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_prep_execve_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:23:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/19 19:35:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	convert_env(t_exe *b)
{
	int		size;
	int		i;
	t_list	*envcpy;

	size = ft_lstsize(*(b->env));
	b->execve_envp = malloc((size + 1) * sizeof(char *));
	if (!b->execve_envp)
	{
		perror("minishell: for execve: malloc fail for envp");
		b->exit_st = ENOMEM;
		return ;
	}
	i = -1;
	envcpy = *(b->env);
	while (envcpy)
	{
		b->execve_envp[++i] = ft_strdup(envcpy->as_str);
		envcpy = envcpy->next;
	}
	b->execve_envp[++i] = NULL;
}

static void	convert_argv(t_ast *s, t_exe *b)
{
	int	i;

	i = -1;
	b->execve_argv = malloc((s->command->size + 1) * sizeof(char *));
	if (!b->execve_argv)
	{
		perror("minishell: for execve: malloc fail for argv");
		b->exit_st = ENOMEM;
		return ;
	}
	while (++i < s->command->size)
		b->execve_argv[i] = ft_strdup(s->command->args[i]);
	b->execve_argv[i] = NULL;
}

void	prep_execve_args(t_ast *s, t_exe *b)
{
	if (!s || !b)
		ft_putstr_fd("minishell: exec: unpopulated parameters\n", 2);
	if (b->execve_envp == NULL)
		convert_env(b);
	convert_argv(s, b);
	seek_path(b);
}
