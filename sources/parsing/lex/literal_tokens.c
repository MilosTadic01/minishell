/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daria <daria@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:16:56 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/28 19:23:35 by daria            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_literal_token(t_input *in)
{
	char	*seq;
	char	*res;
	char	*tmp;

	res = NULL;
	if (!in->current_char)
	{
		init_token(&in->current_token, "", FINAL_TOKEN);
		return (SUCCESS);
	}
	while (in->current_char)
	{
		if (exit_loop_conditions(in))
			break ;
		seq = get_literal_part(in);
		tmp = ft_concat(res, seq);
		free(res);
		free(seq);
		res = tmp;
	}
	init_token(&in->current_token, res, LITERAL);
	return (0);
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
			exit (UNCLOSED_QUOTATIONS);
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
	int		start;

	start = in->current_position;
	if (in->quotations == SINGLE_QUOTE || in->quotations == DOUBLE_QUOTE)
		return (get_quotation_sequence(in));
	else
	{
		if (in->current_char == DOLLAR && ft_isalnum(peek_char(in)))
			return (expand_variable(in, DEFAULT));
		else
		{
			while (in->current_char && in->current_char != SINGLE_QUOTE
				&& in->current_char != DOUBLE_QUOTE
				&& !ft_isspace(in->current_char) && !is_control_char(in))
			{
				if (in->current_char == DOLLAR && !ft_isalnum(peek_char(in)))
				{
					next_char(in);
					break ;
				}
				next_char(in);
			}
			return (ft_substr(in->input, start, in->current_position - start));
		}
	}
}

char	*get_quotation_sequence(t_input *in)
{
	int		start;

	start = in->current_position;
	if (in->quotations == SINGLE_QUOTE)
	{
		while (in->current_char && in->current_char != SINGLE_QUOTE)
			next_char(in);
		return (ft_substr(in->input, start, in->current_position - start));
	}
	else
	{
		if (in->current_char == DOLLAR && ft_isalnum(peek_char(in)))
			return (expand_variable(in, DOUBLE_QUOTE));
		else
		{
			while (in->current_char && in->current_char != DOUBLE_QUOTE
				&& !(in->current_char == DOLLAR && ft_isalnum(peek_char(in))))
				next_char(in);
			return (ft_substr(in->input, start, in->current_position - start));
		}
	}
}

char	*expand_variable(t_input *in, int state)
{
	char	*var_name;
	char	*var_value;
	int		start;

	next_char(in);
	start = in->current_position;
	if (in->current_char == QUESTION_MARK)
	{
		next_char(in);
		return (ft_itoa(errno));
	}
	while (ft_isalnum(in->current_char) || in->current_char == UNDERSCORE)
		next_char(in);
	var_name = ft_substr(in->input, start, in->current_position - start);
	var_value = getenv(var_name);
	if (var_value && !state)
		var_value = ft_rm_consec_spaces(var_value);
	else if (var_value && state)
		var_value = ft_strdup(var_value);
	free(var_name);
	return (var_value);
}
