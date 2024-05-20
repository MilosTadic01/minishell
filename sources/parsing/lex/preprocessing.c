/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:11:03 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/20 17:15:48 by dzubkova         ###   ########.fr       */
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
