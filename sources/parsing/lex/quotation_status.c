/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:15:20 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/15 16:46:21 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	quotation_status(t_input *in)
{
	if (in->quotations == DEFAULT && unclosed_quotations_check(in))
		return (UNCLOSED_QUOTATIONS);
	if (in->current_char == SINGLE_QUOTE && in->quotations == DOUBLE_QUOTE)
		return (SUCCESS);
	if (in->current_char == DOUBLE_QUOTE && in->quotations == SINGLE_QUOTE)
		return (SUCCESS);
	if (in->current_char == DOUBLE_QUOTE)
	{
		if (in->quotations == DOUBLE_QUOTE)
			in->quotations = DEFAULT;
		else if (in->quotations == DEFAULT)
			in->quotations = DOUBLE_QUOTE;
	}
	else if (in->current_char == SINGLE_QUOTE)
	{
		if (in->quotations == SINGLE_QUOTE)
			in->quotations = DEFAULT;
		else if (in->quotations == DEFAULT)
			in->quotations = SINGLE_QUOTE;
	}
	return (SUCCESS);
}

int	unclosed_quotations_check(t_input *in)
{
	int		q;
	char	*copy;

	copy = in->input;
	copy += in->current_position;
	q = *copy;
	if (*(copy + 1))
		copy++;
	else
		return (UNCLOSED_QUOTATIONS);
	while (*copy)
	{
		if (*copy == q)
			return (SUCCESS);
		copy++;
	}
	return (UNCLOSED_QUOTATIONS);
}

int	unclosed_parenthesis_check(t_input *in)
{
	int		nested_count;
	char	*copy;

	nested_count = 0;
	copy = in->input;
	while (*copy)
	{
		if (*copy == OPEN_PARENTHESE)
			nested_count++;
		else if (*copy == CLOSE_PARENTHESE)
			nested_count--;
		copy++;
	}
	if (nested_count)
		return (UNCLOSED_PARENTHESIS);
	return (SUCCESS);
}
