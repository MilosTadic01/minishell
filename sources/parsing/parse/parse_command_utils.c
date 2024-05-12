/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:43:47 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/12 14:07:06 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_redirection(t_input *input, t_ast **ast)
{
	char	*filename;
	int		type;

	type = input->current_token.token_type;
	filename = redir_filename(input);
	if (!filename)
	{
		free_ast(*ast);
		return (PARSING_ERROR);
	}
	append_item(type, filename, ast);
	return (SUCCESS);
}

int	handle_command_argument(t_input *input, t_ast **ast)
{
	char	**tmp;

	tmp = (*ast)->command->args;
	(*ast)->command->args = ft_strappend(tmp,
			input->current_token.value, (*ast)->command->size);
	free_str(tmp, (*ast)->command->size);
	(*ast)->command->size++;
	return (SUCCESS);
}

int	is_command_separator(t_input *input)
{
	if (input->current_token.token_type == PIPE
		|| input->current_token.token_type == AND
		|| input->current_token.token_type == OR)
		return (1);
	return (0);
}
