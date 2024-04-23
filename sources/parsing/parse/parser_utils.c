/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:17:07 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/22 14:31:48 by dzubkova         ###   ########.fr       */
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

	if (!peek_token(in) || peek_token(in)->token_type != LITERAL)
	{
		filename = NULL;
		ft_putstr_fd("PARSING ERROR\n", 2);
		exit (1);
	}
	else
	{
		advance_token(in);
		filename = ft_strdup(in->current_token->value);
	}
	return (filename);
}

t_token	*peek_token(t_input *in)
{
	t_input	*copy;

	if (!in->current_token)
		return (NULL);
	copy = malloc(sizeof(t_input));
	if (!copy)
		return (NULL);
	copy->current_char = in->current_char;
	copy->current_position = in->current_position;
	copy->input = ft_strdup(in->input);
	copy->current_token = in->current_token;
	advance_token(copy);
	return (copy->current_token);
}

int	is_redirection(int type)
{
	if ((type == REDIRECT_IN || type == REDIRECT_IN_IN || type == REDIRECT_OUT
			|| type == REDIRECT_OUT_OUT))
		return (1);
	return (0);
}

void	advance_token(t_input *in)
{
	in->current_token = create_token(in);
}
