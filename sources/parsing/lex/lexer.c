/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:23:32 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/02 11:12:29 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	create_token(t_input *in)
{
	skip_spaces(in);
	if (in->current_char == PIPE)
		return (get_pipe_token(in));
	else if (in->current_char == AMPERSAND)
		return (get_ampersand_token(in));
	else if (in->current_char == REDIRECT_IN)
		return (get_input_redir_token(in));
	else if (in->current_char == REDIRECT_OUT)
		return (get_output_redir_token(in));
	else if (in->current_char == OPEN_PARENTHESE)
		return (get_subshell_token(in));
	else
		return (get_literal_token(in));
	return (-1);
}

void	init_input(t_input *in, char *input_string)
{
	in->current_position = 0;
	in->input = ft_strdup(input_string);
	in->current_char = in->input[0];
	in->quotations = DEFAULT;
	in->current_token.token_type = FINAL_TOKEN;
	in->current_token.value = NULL;
}

void	init_token(t_token *new_token, char *value, int type)
{
	new_token->token_type = type;
	new_token->value = value;
}
