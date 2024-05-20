/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_count_n_fetch.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:02:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/18 02:21:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	go_thru_ins_and_increment_hd_count(t_ast *s, t_exe *b)
{
	t_list	*ins_cpy;

	ins_cpy = s->command->ins;
	while (ins_cpy)
	{
		if (ins_cpy->as_item->type == REDIRECT_IN_IN)
			b->hd_count++;
		ins_cpy = ins_cpy->next;
	}
}

int	count_heredocs(t_ast *s, t_exe *b)
{
	t_ast	*subsh_ast;

	if (!s || !b)
		return (ERROR);
	subsh_ast = NULL;
	if (s->tag == COMMAND && s->command->ins)
		go_thru_ins_and_increment_hd_count(s, b);
	else if (s->tag == SUBSHELL || s->tag == RECCALL)
	{
		subsh_ast = parse(s->subshell_cmd, b);
		if (!subsh_ast)
			return (PARSING_ERROR);
		if (subsh_ast)
			count_heredocs(subsh_ast, b);
		free_ast(subsh_ast);
		subsh_ast = NULL;
	}
	if (s->left)
		count_heredocs(s->left, b);
	if (s->right)
		count_heredocs(s->right, b);
	return (SUCCESS);
}

static void	go_thru_ins_and_dup_delimiters(t_ast *s, t_exe *b)
{
	t_list	*ins_cpy;

	ins_cpy = NULL;
	ins_cpy = s->command->ins;
	while (ins_cpy)
	{
		if (ins_cpy->as_item->type == REDIRECT_IN_IN)
			b->hd_delimiters[++(b->i)] = ft_strdup(ins_cpy->as_item->filename);
		ins_cpy = ins_cpy->next;
	}
}

void	fetch_hd_delimiters(t_ast *s, t_exe *b)
{
	t_ast	*subsh_ast;

	subsh_ast = NULL;
	if (s->tag == COMMAND && s->command->ins)
		go_thru_ins_and_dup_delimiters(s, b);
	if (s->tag == SUBSHELL || s->tag == RECCALL)
	{
		subsh_ast = parse(s->subshell_cmd, b);
		if (!subsh_ast)
			ft_putstr_fd("fetch_hd_delimiters: recursive parsing fail\n", 2);
		else if (subsh_ast)
			fetch_hd_delimiters(subsh_ast, b);
		free_ast(subsh_ast);
	}
	if (s->left)
		fetch_hd_delimiters(s->left, b);
	if (s->right)
		fetch_hd_delimiters(s->right, b);
}
