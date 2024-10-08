/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:17:07 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/20 11:41:14 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	append_item(int type, char *filename, t_ast **ast)
{
	t_list			*redir_node;
	t_redir_item	*item;
	t_type			tmp;

	item = new_item(type, filename);
	tmp = (t_type){.as_item = item};
	redir_node = ft_lstnew(&tmp, AS_ITEM);
	if (type == REDIRECT_IN || type == REDIRECT_IN_IN)
		ft_lstadd_back(&(*ast)->command->ins, redir_node);
	else
		ft_lstadd_back(&(*ast)->command->outs, redir_node);
}

char	*redir_filename(t_input *in)
{
	char	*filename;

	advance_token(in);
	filename = NULL;
	if (is_final_token(in) || in->current_token.token_type != LITERAL)
		return (filename);
	else
		filename = ft_strdup(in->current_token.value);
	return (filename);
}

int	is_final_token(t_input *input)
{
	if (input->current_token.token_type != FINAL_TOKEN)
		return (0);
	return (1);
}

int	is_redirection(int type)
{
	if ((type == REDIRECT_IN || type == REDIRECT_IN_IN || type == REDIRECT_OUT
			|| type == REDIRECT_OUT_OUT))
		return (1);
	return (0);
}

int	advance_token(t_input *in)
{
	int	old_type;

	old_type = in->current_token.token_type;
	if (old_type == LITERAL)
	{
		free(in->current_token.value);
		in->current_token.token_type = FINAL_TOKEN;
	}
	if (create_token(in))
		return (PARSING_ERROR);
	if (old_type == PIPE && is_command_separator(in))
		return (PARSING_ERROR);
	return (SUCCESS);
}
