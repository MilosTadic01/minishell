/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:16:56 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/08 15:22:50 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_literal_token(t_input *in, t_list **env)
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
		if (exit_loop_conditions(in) == UNCLOSED_QUOTATIONS)
			return (UNCLOSED_QUOTATIONS);
		else if (exit_loop_conditions(in))
			break ;
		seq = get_literal_part(in, env);
		if (!seq)
			return (MISSING_OPEN_PARENTHESE);
		tmp = ft_concat(res, seq);
		free(res);
		free(seq);
		res = tmp;
	}
	init_token(&in->current_token, res, LITERAL);
	return (SUCCESS);
}

int	exit_loop_conditions(t_input *in)
{
	if (ft_isspace(in->current_char) && in->quotations == DEFAULT)
		return (1);
	if (in->current_char == SINGLE_QUOTE
		|| in->current_char == DOUBLE_QUOTE)
	{
		if (quotation_status(in))
			return (UNCLOSED_QUOTATIONS);
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

char	*get_literal_part(t_input *in, t_list **env)
{
	int		start;

	start = in->current_position;
	if (in->quotations == SINGLE_QUOTE || in->quotations == DOUBLE_QUOTE)
		return (get_quotation_sequence(in, env));
	if (in->current_char == DOLLAR && (ft_isalnum(peek_char(in))
			|| peek_char(in) == QUESTION_MARK))
		return (expand_variable(in, DEFAULT, env));
	while (in->current_char && !is_literal_end(in))
	{
		if (in->current_char == DOLLAR
			&& (ft_isalnum(peek_char(in)) || peek_char(in) == QUESTION_MARK))
			break ;
		if (in->current_char == CLOSE_PARENTHESE)
			return (NULL);
		next_char(in);
	}
	return (ft_substr(in->input, start, in->current_position - start));
}

char	*get_quotation_sequence(t_input *in, t_list **env)
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
			return (expand_variable(in, DOUBLE_QUOTE, env));
		else
		{
			while (in->current_char && in->current_char != DOUBLE_QUOTE
				&& !(in->current_char == DOLLAR && ft_isalnum(peek_char(in))))
				next_char(in);
			return (ft_substr(in->input, start, in->current_position - start));
		}
	}
}

char	*expand_variable(t_input *in, int state, t_list **env)
{
	char	*var_name;
	char	*var_value;
	int		start;

	next_char(in);
	start = in->current_position;
	if (in->current_char == QUESTION_MARK)
	{
		next_char(in);
		return (ft_itoa(g_exit));
	}
	while (ft_isalnum(in->current_char) || in->current_char == UNDERSCORE)
		next_char(in);
	var_name = ft_substr(in->input, start, in->current_position - start);
	var_value = ft_getenv(var_name, *env);
	if (var_value && !state)
		var_value = ft_rm_consec_spaces(var_value);
	else if (var_value && state)
		var_value = ft_strdup(var_value);
	free(var_name);
	return (var_value);
}
