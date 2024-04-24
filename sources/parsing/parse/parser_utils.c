/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:17:07 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/24 17:20:55 by dzubkova         ###   ########.fr       */
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
	if (is_final(in) || in->current_token.token_type != LITERAL)
	{
		ft_putstr_fd("PARSING ERROR\n", 2);
		exit (1);
	}
	else
		filename = ft_strdup(in->current_token.value);
	return (filename);
}

int	is_final(t_input *input)
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

void	advance_token(t_input *in)
{
	if (in->current_token.token_type == LITERAL)
	{
		free(in->current_token.value);
		in->current_token.token_type = FINAL_TOKEN;
	}
	create_token(in);
}
