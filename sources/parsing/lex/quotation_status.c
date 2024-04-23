/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:15:20 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/18 11:32:13 by dzubkova         ###   ########.fr       */
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
		next_char(in);
	}
	else if (in->current_char == SINGLE_QUOTE)
	{
		if (in->quotations == SINGLE_QUOTE)
			in->quotations = DEFAULT;
		else if (in->quotations == DEFAULT)
			in->quotations = SINGLE_QUOTE;
		next_char(in);
	}
	return (SUCCESS);
}

int	unclosed_quotations_check(t_input *in)
{
	int		q;
	char	*copy;

	copy = ft_strdup(in->input);
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
