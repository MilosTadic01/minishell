/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:30:33 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/02 11:11:53 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	if (is_final_token(input))
		return (ast);
	type = input->current_token.token_type;
	if (type == AND || type == OR)
	{
		advance_token(input);
		if (is_final_token(input))
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
	if (is_final_token(input))
		return (ast);
	if (input->current_token.token_type == PIPE)
	{
		advance_token(input);
		if (is_final_token(input))
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

	if (input->current_token.token_type == SUBSHELL)
	{
		ast = new_subshell(input->current_token.value);
		advance_token(input);
		return (ast);
	}
	ast = new_command();
	while (!is_final_token(input) && input->current_token.token_type != PIPE
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
