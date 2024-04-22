/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:23:32 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/22 12:17:45 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(t_input *in)
{
	t_token	*token;

	token = NULL;
	skip_spaces(in);
	if (in->current_char == PIPE)
		token = get_pipe_token(in);
	else if (in->current_char == AMPERSAND)
		token = get_ampersand_token(in);
	else if (in->current_char == REDIRECT_IN)
		token = get_input_redir_token(in);
	else if (in->current_char == REDIRECT_OUT)
		token = get_output_redir_token(in);
	else
		token = get_literal_token(in);
	return (token);
}

t_input	*new_input(char *input_string)
{
	t_input	*in;

	in = malloc(sizeof(t_input));
	if (!in)
		return (NULL);
	in->current_token = malloc(sizeof(t_token));
	if (!in->current_token)
		return (NULL);
	in->current_position = 0;
	in->input = ft_strdup(input_string);
	in->current_char = in->input[in->current_position];
	in->quotations = DEFAULT;
	in->current_token = NULL;
	return (in);
}

t_token	*new_token(char *value, int type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token_type = type;
	new_token->value = value;
	return (new_token);
}
