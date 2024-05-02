/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:47:31 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/02 11:01:28 by dzubkova         ###   ########.fr       */
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

int	get_ampersand_token(t_input *in)
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
			return (get_literal_token(in));
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

int	get_subshell_token(t_input *in)
{
	char	*value;
	int		start;
	int		nested_count;

	next_char(in);
	nested_count = 0;
	start = in->current_position;
	while (in->current_char && (in->current_char != CLOSE_PARENTHESE || nested_count > 0))
	{
		if (in->current_char == OPEN_PARENTHESE)
			nested_count++;
		else if (in->current_char == CLOSE_PARENTHESE)
			nested_count--;
		next_char(in);
	}
	if (!in->current_char)
	{
		ft_putstr_fd("PARSING ERROR\n", 2);
		return (UNCLOSED_PARENTHESIS);
	}
	value = ft_substr(in->input, start, in->current_position - start);
	init_token(&in->current_token, value, SUBSHELL);
	next_char(in);
	return (SUCCESS);
}

