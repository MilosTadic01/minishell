/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:57:33 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/20 12:25:17 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	preprocess_env(t_input *in, t_exe *b)
{
	char	*res;

	res = NULL;
	if (process_input(in, &res, b))
		return (PARSING_ERROR);
	free(in->input);
	init_input(in, res);
	free(res);
	return (SUCCESS);
}

int	process_input(t_input *in, char **res, t_exe *b)
{
	int	start;

	start = in->current_position;
	while (in->current_char && !is_logical_operator(in)
		&& in->current_char != OPEN_PARENTHESE)
	{
		if ((in->current_char == SINGLE_QUOTE
				|| in->current_char == DOUBLE_QUOTE) && quotation_status(in))
			return (PARSING_ERROR);
		if (in->current_char == DOLLAR && (ft_isalnum(peek_char(in))
				|| peek_char(in) == QUESTION_MARK))
			break ;
		next_char(in);
	}
	return (append_sequence(in, start, res, b));
}

int	append_sequence(t_input *in, int start, char **res, t_exe *b)
{
	char	*seq;
	char	*tmp;
	char	*expanded_seq;

	seq = ft_substr(in->input, start, in->current_position - start);
	tmp = ft_concat(*res, seq);
	free(*res);
	free(seq);
	*res = tmp;
	if (in->current_char == DOLLAR && in->quotations != SINGLE_QUOTE)
	{
		expanded_seq = expand_variable(in, in->quotations, b);
		tmp = ft_concat(*res, expanded_seq);
		free(*res);
		free(expanded_seq);
		*res = tmp;
		return (process_input(in, res, b));
	}
	return (continue_processing(in, res));
}

int	continue_processing(t_input *in, char **res)
{
	int		start;
	char	*seq;
	char	*tmp;

	if (in->current_char)
	{
		start = in->current_position;
		while (in->current_char)
			next_char(in);
		seq = ft_substr(in->input, start, in->current_position - start);
		tmp = ft_concat(*res, seq);
		free(*res);
		free(seq);
		*res = tmp;
	}
	return (SUCCESS);
}

char	*expand_variable(t_input *in, int state, t_exe *b)
{
	char	*var_name;
	char	*var_value;
	int		start;

	next_char(in);
	start = in->current_position;
	if (in->current_char == QUESTION_MARK)
	{
		next_char(in);
		return (ft_itoa(b->exit_st));
	}
	while (ft_isalnum(in->current_char) || in->current_char == UNDERSCORE)
		next_char(in);
	var_name = ft_substr(in->input, start, in->current_position - start);
	var_value = ft_getenv(var_name, *(b->env));
	if (var_value && !state)
		var_value = ft_rm_consec_spaces(var_value);
	else if (var_value && state)
		var_value = ft_strdup(var_value);
	else
		var_value = ft_strdup("");
	free(var_name);
	return (var_value);
}
