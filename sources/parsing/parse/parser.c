/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:30:33 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/26 16:36:42 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	free_str(char **str, int size);

t_ast	*parse(char *input_string)
{
	t_input	in;
	t_ast	*final_ast;

	init_input(&in, input_string);
	advance_token(&in);
	final_ast = parse_statement(&in);
	free(in.input);
	return (final_ast);
}

t_ast	*parse_statement(t_input *input)
{
	t_ast	*ast;
	t_ast	*rest;
	int		type;

	ast = parse_pipe(input);
	if (input->current_token.token_type == FINAL_TOKEN)
		return (ast);
	type = input->current_token.token_type;
	if (type == AND || type == OR)
	{
		advance_token(input);
		if (input->current_token.token_type == FINAL_TOKEN)
		{
			ft_putstr_fd("PARSING ERROR\n", 2);
			exit (1);
		}
		rest = parse_statement(input);
		ast = new_binop(type, &ast, &rest);
	}
	return (ast);
}

t_ast	*parse_pipe(t_input *input)
{
	t_ast	*ast;
	t_ast	*rest;

	ast = parse_command(input);
	if (input->current_token.token_type == FINAL_TOKEN)
		return (ast);
	if (input->current_token.token_type == PIPE)
	{
		advance_token(input);
		if (input->current_token.token_type == FINAL_TOKEN)
		{
			ft_putstr_fd("PARSING ERROR\n", 2);
			exit (1);
		}
		rest = parse_pipe(input);
		ast = new_binop(PIPE, &ast, &rest);
	}
	return (ast);
}

t_ast	*parse_command(t_input *input)
{
	char		**tmp;
	char		*filename;
	int			type;
	t_ast		*ast;

	ast = new_command();
	while (!is_final(input) && input->current_token.token_type != PIPE
			&& input->current_token.token_type != AND
			&& input->current_token.token_type != OR)
	{
		type = input->current_token.token_type;
		if (is_redirection(type))
		{
			filename = redir_filename(input);
			append_item(type, filename, &ast);
		}
		else
		{
			tmp = ast->command->args;
			ast->command->args = ft_strappend(tmp,
					input->current_token.value, ast->command->size);
			free_str(tmp, ast->command->size);
			ast->command->size++;
		}
		advance_token(input);
	}
	return (ast);
}

static void	free_str(char **str, int size)
{
	int	idx;

	idx = 0;
	while (idx < size)
	{
		free(str[idx]);
		idx++;
	}
	free(str);
}
