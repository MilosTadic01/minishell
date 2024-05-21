/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:53:06 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/21 11:54:52 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_subshell_token(t_input *in)
{
	char	*value;
	int		start;
	int		nested_count;

	next_char(in);
	nested_count = 1;
	start = in->current_position;
	while (in->current_char && nested_count)
	{
		if (in->current_char == OPEN_PARENTHESE)
			nested_count++;
		else if (in->current_char == CLOSE_PARENTHESE)
			nested_count--;
		next_char(in);
	}
	value = ft_substr(in->input, start, in->current_position - start - 1);
	if (!ft_strlen(value))
	{
		free(value);
		return (PARSING_ERROR);
	}
	init_token(&in->current_token, value, SUBSHELL);
	next_char(in);
	return (SUCCESS);
}

int	get_recursive_token(t_input *in)
{
	char	*value;
	int		start;

	start = in->current_position;
	while (in->current_char)
		next_char(in);
	value = ft_substr(in->input, start, in->current_position - start);
	if (!ft_strlen(value))
	{
		free(value);
		return (PARSING_ERROR);
	}
	init_token(&in->current_token, value, RECCALL);
	return (SUCCESS);
}

int	is_logical_operator(t_input *in)
{
	if (in->current_char == PIPE && peek_char(in) == PIPE)
		return (1);
	if (in->current_char == AMPERSAND && peek_char(in) == AMPERSAND)
		return (1);
	return (0);
}
