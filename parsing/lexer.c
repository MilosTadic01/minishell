/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:28:43 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/01 18:54:24 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	lex_input(char *string)
{
	t_input	in;

	in.input = string;
	in.current_char = *string;
	in.current_position = 0;
	in.quotations = 0;
	return (in);
}

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

void	init_token(t_token *new_token, t_input *in, char *value, int type)
{
	int	size;

	size = (int)ft_strlen(value);
	new_token->token_type = type;
	new_token->value = value;
	while (size--)
		get_next_char(in);
}

void	get_next_token(t_token *next_token, t_input *in)
{
	skip_spaces(in);
	if (in->current_char == '\"' && in->quotations == 2)
	{
		in->quotations = 0;
		get_next_char(in);
	}
	skip_spaces(in);
	if (in->quotations == 2 && in->current_char != '\"' && in->current_char != '$')
	{
		get_quotation_tokens(in, next_token);
	}
	else if (in->current_char == '\"' && in->quotations == 0)
	{
		in->quotations = 2;
		get_next_char(in);
		get_quotation_tokens(in, next_token);
	}
	else if (in->current_char == '|')
	{
		if (peek_next_char(*in) == '|')
			init_token(next_token, in, "||", OR);
		else
			init_token(next_token, in, "|", PIPE);
	}
	else if (in->current_char == '$')
	{
		if (peek_next_char(*in) == '?')
			init_token(next_token, in, "$?", EXIT_STATUS);
		else
		{
			get_next_char(in);
			get_variable_token(next_token, in);
		}
	}
	else if (in->current_char == '<')
	{
		if (peek_next_char(*in) == '<')
			init_token(next_token, in, "<<", READ_DELIM);
		else
			init_token(next_token, in, "<", REDIRECT_IN);
	}
	else if (in->current_char == '>')
	{
		if (peek_next_char(*in) == '>')
			init_token(next_token, in, ">>", APPEND_OUT);
		else
			init_token(next_token, in, ">", REDIRECT_OUT);
	}
	else if (in->current_char == '&' && peek_next_char(*in) == '&')
		init_token(next_token, in, "&&", AND);
	else
		get_char_sequence(in, next_token);
}

void	get_variable_token(t_token *next_token, t_input *in)
{
	char	*var_name;
	int		start;

	start = in->current_position;
	while (ft_isalnum(in->current_char) || in->current_char == '_')
		get_next_char(in);
	var_name = ft_substr(in->input, start, in->current_position - start);
	next_token->token_type = VARIABLE;
	next_token->value = var_name;
}

void	skip_spaces(t_input *in)
{
	while (ft_isspace(in->current_char))
	{
		in->current_position++;
		in->current_char = in->input[in->current_position];
	}
}

void	get_char_sequence(t_input *in, t_token *next_token)
{
	int		start;
	char	*seq;

	start = in->current_position;
	while (!ft_isspace(in->current_char) && !is_control_char(*in))
		get_next_char(in);
	//add NULL-check for seq
	seq = ft_substr(in->input, start, in->current_position - start);
	next_token->token_type = match_builtin(seq);
	next_token->value = seq;
}

void get_quotation_tokens(t_input *in, t_token *next_token)
{
	int		start;
	char	*seq;

	start = in->current_position;
	if (in->quotations == 1)
	{
		while (in->current_char != '\'')
			get_next_char(in);
		seq = ft_substr(in->input, start, in->current_position - start);
		next_token->token_type = LITERAL;
		next_token->value = seq;
		get_next_char(in);
	}
	if (in->quotations == 2)
	{
		while (in->current_char != '$' && in->current_char != '\"')
			get_next_char(in);
		seq = ft_substr(in->input, start, in->current_position - start);
		next_token->token_type = LITERAL;
		next_token->value = seq;
	}
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

int	is_control_char(t_input in)
{
	if (ft_strchr("|$<>", in.current_char))
		return (1);
	if (in.current_char == '&' && peek_next_char(in) == '&')
		return (1);
	return (0);
}
