/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:16:56 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/12 14:01:09 by dzubkova         ###   ########.fr       */
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
		init_token(&in->current_token, "", FINAL_TOKEN);
	while (in->current_char)
	{
		if (exit_loop_conditions(in) == UNCLOSED_QUOTATIONS)
			return (UNCLOSED_QUOTATIONS);
		else if (exit_loop_conditions(in))
			break ;
		seq = get_literal_part(in);
		if (!seq)
			return (MISSING_OPEN_PARENTHESE);
		tmp = ft_concat(res, seq);
		free(res);
		free(seq);
		res = tmp;
	}
	if (res)
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
		next_char(in);
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
	while (in->current_char && !is_literal_end(in))
	{
		if (in->current_char == CLOSE_PARENTHESE)
			return (NULL);
		next_char(in);
	}
	return (ft_substr(in->input, start, in->current_position - start));
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
		while (in->current_char && in->current_char != DOUBLE_QUOTE
			&& !(in->current_char == DOLLAR && ft_isalnum(peek_char(in))))
			next_char(in);
		return (ft_substr(in->input, start, in->current_position - start));
	}
}
