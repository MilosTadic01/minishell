/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:47:31 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/08 12:53:29 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_output_redir_token(t_input *in)
{
	if (in->current_char == REDIRECT_OUT && peek_char(in) == REDIRECT_OUT)
	{
		init_token(&in->current_token, ">>", REDIRECT_OUT_OUT);
		next_char(in);
		next_char(in);
	}
	else
	{
		init_token(&in->current_token, ">", REDIRECT_OUT);
		next_char(in);
	}
	return (SUCCESS);
}

int	get_input_redir_token(t_input *in)
{
	if (in->current_char == REDIRECT_IN && peek_char(in) == REDIRECT_IN)
	{
		init_token(&in->current_token, "<<", REDIRECT_IN_IN);
		next_char(in);
		next_char(in);
	}
	else
	{
		init_token(&in->current_token, "<", REDIRECT_IN);
		next_char(in);
	}
	return (SUCCESS);
}

int	get_ampersand_token(t_input *in, t_list **env)
{
	if (in->current_char == AMPERSAND)
	{
		if (peek_char(in) == AMPERSAND)
		{
			init_token(&in->current_token, "&&", AND);
			next_char(in);
			next_char(in);
		}
		else
			return (get_literal_token(in, env));
	}
	return (SUCCESS);
}

int	get_pipe_token(t_input *in)
{
	if (in->current_char == PIPE)
	{
		if (peek_char(in) == PIPE)
		{
			init_token(&in->current_token, "||", OR);
			next_char(in);
			next_char(in);
		}
		else
		{
			init_token(&in->current_token, "|", PIPE);
			next_char(in);
		}
	}
	return (SUCCESS);
}
