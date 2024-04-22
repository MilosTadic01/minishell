/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:30:33 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/22 14:32:21 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast	*parse(char *input_string)
{
	t_input	*in;
	t_ast	*final_ast;

	in = new_input(input_string);
	advance_token(in);
	if (!in)
	{
		ft_putstr_fd("ERROR: failed to initialize input\n", 2);
		return (NULL);
	}
	final_ast = parse_statement(in);
	return (final_ast);
}

t_ast	*parse_statement(t_input *input)
{
	t_ast	*ast;
	t_ast	*rest;

	ast = parse_command(input);
	if (!input->current_token)
		return (ast);
	if (input->current_token->token_type == PIPE)
	{
		advance_token(input);
		rest = parse_statement(input);
		ast = new_binop(PIPE, &ast, &rest);
	}
	return (ast);
}

t_ast	*parse_command(t_input *in)
{
	char			*filename;
	int				type;
	t_ast			*ast;

	ast = new_command();
	while (in->current_token && in->current_token->token_type != PIPE)
	{
		type = in->current_token->token_type;
		if (is_redirection(type))
		{
			filename = redir_filename(in);
			append_item(type, filename, &ast);
		}
		else
		{
			ast->command->args = ft_strappend(ast->command->args,
					in->current_token->value, ast->command->size);
			ast->command->size++;
		}
		advance_token(in);
	}
	return (ast);
}
