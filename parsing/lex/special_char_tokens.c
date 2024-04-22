/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:47:31 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/18 11:19:01 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*get_output_redir_token(t_input *in)
{
	t_token	*token;

	token = NULL;
	if (in->current_char == REDIRECT_OUT && peek_char(in) == REDIRECT_OUT)
	{
		token = new_token(">>", REDIRECT_OUT_OUT);
		next_char(in);
		next_char(in);
	}
	else
	{
		token = new_token(">", REDIRECT_OUT);
		next_char(in);
	}
	return (token);
}

t_token	*get_input_redir_token(t_input *in)
{
	t_token	*token;

	token = NULL;
	if (in->current_char == REDIRECT_IN && peek_char(in) == REDIRECT_IN)
	{
		token = new_token("<<", REDIRECT_IN_IN);
		next_char(in);
		next_char(in);
	}
	else
	{
		token = new_token("<", REDIRECT_IN);
		next_char(in);
	}
	return (token);
}

t_token	*get_ampersand_token(t_input *in)
{
	t_token	*token;

	token = NULL;
	if (in->current_char == AMPERSAND)
	{
		if (peek_char(in) == AMPERSAND)
		{
			token = new_token("&&", AND);
			next_char(in);
			next_char(in);
		}
		else
			token = get_literal_token(in);
	}
	return (token);
}

t_token	*get_pipe_token(t_input *in)
{
	t_token	*token;

	token = NULL;
	if (in->current_char == PIPE)
	{
		if (peek_char(in) == PIPE)
		{
			token = new_token("||", OR);
			next_char(in);
			next_char(in);
		}
		else
		{
			token = new_token("|", PIPE);
			next_char(in);
		}
	}
	return (token);
}
