/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:23:32 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/17 15:06:06 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//EXIT STATUS?

void	extract_tokens(char *input_string)
{
	t_input	*in;
	t_token	*token;

	in = new_input(input_string);
	token = NULL;
	if (!in)
	{
		ft_putstr_fd("ERROR: failed to initialize input\n", 2);
		return ;
	}
	//here it's gonna pass tokens to parser instead of printing them
	while ((token = create_token(in)))
		printf("%s\n", token->value);
}

t_input	*new_input(char *input_string)
{
	t_input	*in;

	in = malloc(sizeof(t_input));
	if (!in)
		return (NULL);
	in->current_position = 0;
	in->input = ft_strdup(input_string);
	in->current_char = in->input[in->current_position];
	in->quotations = DEFAULT;
	return (in);
}

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

t_token	*create_token(t_input *in)
{
	t_token	*token;

	token = NULL;
	skip_spaces(in);
	if (in->current_char == PIPE)
		token = get_pipe_token(in);
	else if (in->current_char == AMPERSAND)
		token = get_ampersand_token(in);
	else if (in->current_char == REDIRECT_IN)
		token = get_input_redir_token(in);
	else if (in->current_char == REDIRECT_OUT)
		token = get_output_redir_token(in);
	else
		token = get_literal_token(in);
	return (token);
}

t_token	*get_literal_token(t_input *in)
{
	char	*seq;
	char	*res;
	t_token	*token;

	token = NULL;
	res = NULL;
	if (!in->current_char)
		return (token);
	while (in->current_char)
	{
		if (ft_isspace(in->current_char) && in->quotations == DEFAULT)
			break ;
		if (in->current_char == SINGLE_QUOTE || in->current_char == DOUBLE_QUOTE)
		{
			if (quotation_status(in))
			{
				ft_putstr_fd("PARSING ERROR\n", 2);
				return (NULL);
			}
			if (!in->current_char)
				break ;
		}
		if (in->quotations == DEFAULT)
		{
			if (is_control_char(in))
				break ;
			else if (ft_isspace(in->current_char))
				break ;
		}
		seq = get_literal_part(in);
		res = ft_concat(res, seq);
	}
	token = new_token(res, LITERAL);
	return (token);
}

char	*get_literal_part(t_input *in)
{
	char	*seq;
	int		start;

	start = in->current_position;
	if (in->quotations == SINGLE_QUOTE || in->quotations == DOUBLE_QUOTE)
		seq = get_quotation_sequence(in);
	else
	{
		if (in->current_char == DOLLAR)
			seq = expand_variable(in, DEFAULT);
		else
		{
			while (in->current_char && in->current_char != SINGLE_QUOTE && in->current_char != DOUBLE_QUOTE
					&& in->current_char != DOLLAR)
			{
				if (ft_isspace(in->current_char))
					break ;
				if (is_control_char(in))
					break ;
				next_char(in);
			}
			seq = ft_substr(in->input, start, in->current_position - start);
		}
	}
	return (seq);
}

char	*get_quotation_sequence(t_input *in)
{
	char	*seq;
	int		start;

	start = in->current_position;
	seq = NULL;
	if (in->quotations == SINGLE_QUOTE)
	{
		while (in->current_char && in->current_char != SINGLE_QUOTE)
			next_char(in);
		seq = ft_substr(in->input, start, in->current_position - start);
	}
	else if (in->quotations == DOUBLE_QUOTE)
	{
		if (in->current_char == DOLLAR)
			seq = expand_variable(in, DOUBLE_QUOTE);
		else
		{
			while (in->current_char && in->current_char != DOLLAR && in->current_char != DOUBLE_QUOTE)
				next_char(in);
			seq = ft_substr(in->input, start, in->current_position - start);
		}
	}
	return (seq);
}

char	*expand_variable(t_input *in, int state)
{
	char	*tmp_value;
	char	*var_name;
	int		start;

	next_char(in);
	start = in->current_position;
	while (ft_isalnum(in->current_char) || in->current_char == UNDERSCORE || in->current_char == QUESTION_MARK)
		next_char(in);
	var_name = ft_substr(in->input, start, in->current_position - start);
	tmp_value = getenv(var_name);
	if (tmp_value && state)
		tmp_value = ft_rm_consec_spaces(tmp_value);
	return (tmp_value);
}

t_token	*get_output_redir_token(t_input *in)
{
	t_token	*token;

	token = NULL;
	if (in->current_char == REDIRECT_OUT && peek_char(in) == REDIRECT_OUT)
	{
		token = new_token(">>", REDIRECT_OUT_OUT);
		next_char(in);
		next_char(in);
	}
	else
	{
		token = new_token(">", REDIRECT_OUT);
		next_char(in);
	}
	return (token);
}

t_token	*get_input_redir_token(t_input *in)
{
	t_token	*token;

	token = NULL;
	if (in->current_char == REDIRECT_IN && peek_char(in) == REDIRECT_IN)
	{
		token = new_token("<<", REDIRECT_IN_IN);
		next_char(in);
		next_char(in);
	}
	else
	{
		token = new_token("<", REDIRECT_IN);
		next_char(in);
	}
	return (token);
}

t_token	*get_ampersand_token(t_input *in)
{
	t_token	*token;

	token = NULL;
	if (in->current_char == AMPERSAND)
	{
		if (peek_char(in) == AMPERSAND)
		{
			token = new_token("&&", AND);
			next_char(in);
			next_char(in);
		}
		else
			token = get_literal_token(in);
	}
	return (token);
}

t_token	*get_pipe_token(t_input *in)
{
	t_token	*token;

	token = NULL;
	if (in->current_char == PIPE)
	{
		if (peek_char(in) == PIPE)
		{
			token = new_token("||", OR);
			next_char(in);
			next_char(in);
		}
		else
		{
			token = new_token("|", PIPE);
			next_char(in);
		}
	}
	return (token);
}

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

t_token	*new_token(char *value, int type)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token_type = type;
	new_token->value = value;
	return (new_token);
}

int	is_control_char(t_input *in)
{
	if (in->current_char == PIPE || in->current_char == REDIRECT_IN || in->current_char == REDIRECT_OUT)
		return (1);
	if (in->current_char == AMPERSAND && peek_char(in) == AMPERSAND)
		return (1);
	return (0);
}