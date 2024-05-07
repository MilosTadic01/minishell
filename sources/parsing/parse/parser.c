/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:30:33 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/07 17:30:05 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_ast	*parse(char *input_string, t_list **env)
{
	int		type;
	t_ast	*final_ast;
	t_input	in;

	init_input(&in, input_string);
	if (advance_token(&in, env))
		return (NULL);
	type = in.current_token.token_type;
	if (type == PIPE || type == AND || type == OR)
	{
		free(in.input);
		return (NULL);
	}
	final_ast = parse_statement(&in, env);
	free(in.input);
	return (final_ast);
}

t_ast	*parse_statement(t_input *input, t_list **env)
{
	t_ast	*ast;
	t_ast	*rest;
	int		type;

	ast = parse_pipe(input, env);
	if (!ast)
		return (NULL);
	if (is_final_token(input))
		return (ast);
	type = input->current_token.token_type;
	if (type == AND || type == OR)
	{
		advance_token(input, env);
		if (is_final_token(input))
		{
			free_ast(ast);
			return (NULL);
		}
		rest = parse_statement(input, env);
		if (!rest)
			return (NULL);
		ast = new_binop(type, &ast, &rest);
	}
	return (ast);
}

t_ast	*parse_pipe(t_input *input, t_list **env)
{
	t_ast	*ast;
	t_ast	*rest;

	ast = parse_command(input, env);
	if (!ast)
		return (NULL);
	if (is_final_token(input))
		return (ast);
	if (input->current_token.token_type == PIPE)
	{
		advance_token(input, env);
		if (is_final_token(input))
		{
			free_ast(ast);
			return (NULL);
		}
		rest = parse_pipe(input, env);
		if (!rest)
		{
			free_ast(rest);
			return (NULL);
		}
		ast = new_binop(PIPE, &ast, &rest);
	}
	return (ast);
}

t_ast	*parse_command(t_input *input, t_list **env)
{
	t_ast		*ast;

	if (input->current_token.token_type == SUBSHELL)
	{
		ast = parse_subshell(input, env);
		return (ast);
	}
	ast = new_command();
	while (!is_final_token(input) && !is_command_separator(input))
	{
		if (is_redirection(input->current_token.token_type))
		{
			if (handle_redirection(input, env, &ast))
				return (NULL);
		}
		else
			handle_command_argument(input, &ast);
		if (advance_token(input, env))
		{
			free_ast(ast);
			return (NULL);
		}
	}
	return (ast);
}

t_ast	*parse_subshell(t_input *input, t_list **env)
{
	t_ast		*ast;

	ast = new_subshell(input->current_token.value);
	if (advance_token(input, env))
	{
		free_ast(ast);
		return (NULL);
	}
	if (input->current_token.token_type != AND
		&& input->current_token.token_type != OR
		&& input->current_token.token_type != FINAL_TOKEN)
		return (NULL);
	return (ast);
}
