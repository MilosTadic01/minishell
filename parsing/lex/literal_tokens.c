/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:16:56 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/19 11:12:09 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//$ as LITERAL
t_token	*get_literal_token(t_input *in)
{
	char	*seq;
	char	*res;
	t_token	*token;

	token = NULL;
	res = NULL;
	if (!in->current_char)
		return (token);
	while (in->current_char)
	{
		if (exit_loop_conditions(in))
			break ;
		seq = get_literal_part(in);
		res = ft_concat(res, seq);
	}
	token = new_token(res, LITERAL);
	return (token);
}

int	exit_loop_conditions(t_input *in)
{
	if (ft_isspace(in->current_char) && in->quotations == DEFAULT)
		return (1);
	if (in->current_char == SINGLE_QUOTE
		|| in->current_char == DOUBLE_QUOTE)
	{
		if (quotation_status(in))
		{
			ft_putstr_fd("PARSING ERROR\n", 2);
			return (UNCLOSED_QUOTATIONS);
		}
		if (!in->current_char)
			return (1);
	}
	if (in->quotations == DEFAULT)
	{
		if (is_control_char(in))
			return (1);
		else if (ft_isspace(in->current_char))
			return (1);
	}
	return (0);
}

char	*get_literal_part(t_input *in)
{
	char	*seq;
	int		start;

	start = in->current_position;
	if (in->quotations == SINGLE_QUOTE || in->quotations == DOUBLE_QUOTE)
		seq = get_quotation_sequence(in);
	else
	{
		if (in->current_char == DOLLAR)
			seq = expand_variable(in, DEFAULT);
		else
		{
			while (in->current_char && in->current_char != SINGLE_QUOTE
				&& in->current_char != DOUBLE_QUOTE
				&& in->current_char != DOLLAR)
			{
				if (ft_isspace(in->current_char) || is_control_char(in))
					break ;
				next_char(in);
			}
			seq = ft_substr(in->input, start, in->current_position - start);
		}
	}
	return (seq);
}

char	*get_quotation_sequence(t_input *in)
{
	char	*seq;
	int		start;

	start = in->current_position;
	seq = NULL;
	if (in->quotations == SINGLE_QUOTE)
	{
		while (in->current_char && in->current_char != SINGLE_QUOTE)
			next_char(in);
		seq = ft_substr(in->input, start, in->current_position - start);
	}
	else if (in->quotations == DOUBLE_QUOTE)
	{
		if (in->current_char == DOLLAR)
			seq = expand_variable(in, DOUBLE_QUOTE);
		else
		{
			while (in->current_char && in->current_char != DOLLAR
				&& in->current_char != DOUBLE_QUOTE)
				next_char(in);
			seq = ft_substr(in->input, start, in->current_position - start);
		}
	}
	return (seq);
}

char	*expand_variable(t_input *in, int state)
{
	char	*tmp_value;
	char	*var_name;
	int		start;

	next_char(in);
	start = in->current_position;
	if (in->current_char == QUESTION_MARK)
	{
		tmp_value = ft_itoa(errno);
		next_char(in);
		return (tmp_value);
	}
	while (ft_isalnum(in->current_char) || in->current_char == UNDERSCORE)
		next_char(in);
	var_name = ft_substr(in->input, start, in->current_position - start);
	tmp_value = getenv(var_name);
	if (tmp_value && !state)
		tmp_value = ft_rm_consec_spaces(tmp_value);
	return (tmp_value);
}
