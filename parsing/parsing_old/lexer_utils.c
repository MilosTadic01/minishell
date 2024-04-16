/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:31:41 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/04 10:27:16 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_next_char(t_input *in)
{
	in->current_position += 1;
	if (in->current_position > (int)ft_strlen(in->input))
		in->current_char = '\0';
	else
		in->current_char = in->input[in->current_position];
}

char	peek_next_char(t_input in)
{
	if (in.current_position + 1 >= (int)ft_strlen(in.input))
		return ('\0');
	else
		return (in.input[in.current_position + 1]);
}

int	is_control_char(t_input in)
{
	if (ft_strchr("|$<>", in.current_char))
		return (1);
	if (in.current_char == '&' && peek_next_char(in) == '&')
		return (1);
	return (0);
}

void	skip_spaces(t_input *in)
{
	while (ft_isspace(in->current_char))
	{
		in->current_position++;
		in->current_char = in->input[in->current_position];
	}
}

t_input	initialize_input(char *command_string)
{
	t_input	in;

	in.input = command_string;
	in.current_char = *command_string;
	in.current_position = 0;
	in.quotations = 0;
	in.token_initialized = 0;
	return (in);
}

int	match_builtin(char *seq)
{
	if (!ft_strncmp(seq, "echo", ft_max((int)ft_strlen(seq), 5)))
		return (ECHO);
	if (!ft_strncmp(seq, "cd", ft_max((int)ft_strlen(seq), 3)))
		return (CD);
	if (!ft_strncmp(seq, "pwd", ft_max((int)ft_strlen(seq), 4)))
		return (PWD);
	if (!ft_strncmp(seq, "export", ft_max((int)ft_strlen(seq), 7)))
		return (EXPORT);
	if (!ft_strncmp(seq, "unset", ft_max((int)ft_strlen(seq), 6)))
		return (UNSET);
	if (!ft_strncmp(seq, "env", ft_max((int)ft_strlen(seq), 4)))
		return (ENV);
	if (!ft_strncmp(seq, "exit", ft_max((int)ft_strlen(seq), 5)))
		return (EXIT);
	else
		return (LITERAL);
}