/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:31:41 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/07 12:18:06 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	next_char(t_input *in)
{
	in->current_position += 1;
	if (in->current_position > (int)ft_strlen(in->input))
		in->current_char = '\0';
	else
		in->current_char = in->input[in->current_position];
}

void	skip_spaces(t_input *in)
{
	while (ft_isspace(in->current_char))
	{
		in->current_position++;
		in->current_char = in->input[in->current_position];
	}
}

char	peek_char(t_input *in)
{
	if (in->current_position + 1 >= (int)ft_strlen(in->input))
		return ('\0');
	else
		return (in->input[in->current_position + 1]);
}

int	is_control_char(t_input *in)
{
	if (in->current_char == PIPE || in->current_char == REDIRECT_IN
		|| in->current_char == REDIRECT_OUT)
		return (1);
	if (in->current_char == AMPERSAND && peek_char(in) == AMPERSAND)
		return (1);
	return (0);
}

int	is_literal_end(t_input *in)
{
	return (in->current_char == SINGLE_QUOTE
		|| in->current_char == DOUBLE_QUOTE
		|| ft_isspace(in->current_char)
		|| is_control_char(in));
}
