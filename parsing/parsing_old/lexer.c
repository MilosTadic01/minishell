/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:28:43 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/11 14:58:59 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lex_input(char *string)
{
	t_input	in;
	t_list	*token_list;
	t_token next_token;

	token_list = NULL;
	in = initialize_input(string);
	while (in.current_char)
	{
		get_next_token(&next_token, &in);
		if (in.token_initialized)
			ft_lstadd_back(&token_list, ft_lstnew(&(t_type){.as_token = &next_token}, AS_TOKEN));
	}
	return (token_list);
}

void	init_token(t_token *new_token, t_input *in, char *value, int type)
{
	new_token->token_type = type;
	new_token->value = value;
	in->token_initialized = 1;
}

void	get_next_token(t_token *next_token, t_input *in)
{
	int	flag;

	in->token_initialized = 0;
	skip_spaces(in);
	flag = 0;
	reset_quotes(in, &flag);
	if (!flag)
		get_quotes_literals(next_token, in, &flag);
	if (!flag)
		get_pipes_variables(next_token, in, &flag);
	if (!flag)
		get_redirections(next_token, in, &flag);
	if (!flag)
		get_and_option(next_token, in, &flag);
	if (!flag)
		get_char_sequence(in, next_token);
}

void	get_variable_value(t_token *next_token, t_input *in)
{
	char	*tmp_value;
	char	*var_name;
	int		start;

	start = in->current_position;
	while (ft_isalnum(in->current_char) || in->current_char == '_')
		get_next_char(in);
	var_name = ft_substr(in->input, start, in->current_position - start);
	tmp_value = getenv(var_name);
	if (tmp_value)
		init_token(next_token, in, tmp_value, LITERAL);
}

void	get_char_sequence(t_input *in, t_token *next_token)
{
	int		start;
	char	*seq;

	start = in->current_position;
	while (!ft_isspace(in->current_char) && !is_control_char(*in))
	{
		if (in->current_char == '\'' || in->current_char == '\"')
			break ;
		get_next_char(in);
	}
	seq = ft_substr(in->input, start, in->current_position - start);
	if (!seq)
		return ;
	if (ft_strlen(seq))
	{
		if (in->current_char == '=')
			init_token(next_token, in, seq, VARIABLE);
		else
			init_token(next_token, in, seq, match_builtin(seq));
	}
}

void	get_quotation_tokens(t_input *in, t_token *next_token)
{
	int		start;
	char	*seq;

	start = in->current_position;
	if (in->quotations == 1)
	{
		while (in->current_char != '\'')
			get_next_char(in);
	}
	if (in->quotations == 2)
	{
		while (in->current_char != '$' && in->current_char != '\"')
			get_next_char(in);
	}
	seq = ft_substr(in->input, start, in->current_position - start);
	if (ft_strlen(seq))
		init_token(next_token, in, seq, LITERAL);
}

// goget, gather, extract,
