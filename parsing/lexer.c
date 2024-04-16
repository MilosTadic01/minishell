/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:23:32 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/12 17:46:38 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*t_token	*extract_tokens(char *input_string)
{
	//initializes a t_input data stucture with input string
	//iterates on the string till the end
	//when gets a token, returns it
	//if gets NULL, throws an invalid syntax error
}*/

int	quotation_status(t_input *in)
{
	if (unclosed_quotations_check(in))
		return (UNCLOSED_QUOTATIONS);
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
	t_input	*copy;

	copy = in;
	q = copy->current_char;
	while (copy->current_char)
	{
		if (copy->current_char == q)
			return (SUCCESS);
		next_char(copy);
	}
	return (UNCLOSED_QUOTATIONS);
}

t_token	*create_token(t_input *in)
{
	t_token	*token;

	token = NULL;
	skip_spaces(in);
	//parses next token, taking into account quotations status
	//case 1: arbitrary character
	//			if quotes close, peek further to make sure that it's the end of a literal, else keep parsing
	//case 2: |
	//			DEFAULT + OR
	//			DEFAULT + PIPE
	//			*_QUOTES + OR
	//			*_QUOTES + PIPE
	//case 3:
	//			DEFAULT + &&
	//			*_QUOTES + &&
	if (in->current_char == PIPE)
		token = get_pipe_token(in);
	else if (in->current_char == AMPERSAND)
		token = get_ampersand_token(in);
	//case 4: <
	//			DEFAULT + <<
	//			DEFAULT + <
	//			*_QUOTES + <<
	//			*_QUOTES + <
	else if (in->current_char == REDIRECT_IN)
		token = get_input_redir_token(in);
	//case 5: >
	//			DEFAULT + >>
	//			DEFAULT + >
	//			*_QUOTES + >>
	//			*_QUOTES + >
	else if (in->current_char == REDIRECT_OUT)
		token = get_output_redir_token(in);
	//case 6: $
	//			DEFAULT + $
	//			SINGLE_QUOTES + $
	//			DOUBLE_QUOTES + $
	//else if (in->current_char == DOLLAR)
	//	token = get_variable_value_token(in);
	else
		token = get_literal_token(in);
	return (token);
}

t_token	*get_literal_token(t_input *in)
{
	char	*seq;
	//char	*res;
	t_token	*token;

	token = NULL;
	while (in->current_char && !ft_isspace(in->current_char) && in->current_char != PIPE)
	{
		skip_spaces(in);
		if (in->current_char == SINGLE_QUOTE || in->current_char == DOUBLE_QUOTE)
		{
			if (quotation_status(in))
				return (NULL);
		}
		if (!in->current_char)
			break ;
		if (in->current_char == AMPERSAND && peek_char(in) == AMPERSAND)
			break ;
		else if (in->current_char == PIPE)
			break ;
		else if (in->current_char == REDIRECT_IN || in->current_char == REDIRECT_OUT)
			break ;
		seq = get_literal_part(in);
		printf("%s", seq);
		//res = ft_concat(res, seq);
	}
	//token = new_token(res, LITERAL);
	return (token);
}

char	*get_literal_part(t_input *in)
{
	char	*seq;
	int		start;

	start = in->current_position;
	if (in->quotations == SINGLE_QUOTE)
	{
		while (in->current_char != SINGLE_QUOTE)
			next_char(in);
		seq = ft_substr(in->input, start, in->current_position - start);
	}
	else if (in->quotations == DOUBLE_QUOTE)
	{
		if (in->current_char == DOLLAR)
		{
			next_char(in);
			seq = expand_variable(in, DOUBLE_QUOTE);
		}
		else
		{
			while (in->current_char != DOLLAR && in->current_char != DOUBLE_QUOTE)
				next_char(in);
			seq = ft_substr(in->input, start, in->current_position - start);
		}
	}
	else
	{
		if (in->current_char == DOLLAR)
			seq = expand_variable(in, DEFAULT);
		while (in->current_char != SINGLE_QUOTE && in->current_char != DOUBLE_QUOTE
					&& in->current_char != DOLLAR)
		{
			if (ft_isspace(in->current_char))
				break ;
			next_char(in);
		}
		seq = ft_substr(in->input, start, in->current_position - start);
	}
	return (seq);
}

/*char	*get_quotation_literal(t_input *in, int quote_type)
{
	;
}*/

char	*expand_variable(t_input *in, int state)
{
	char	*tmp_value;
	char	*var_name;
	int		start;

	start = in->current_position;
	while (ft_isalnum(in->current_char) || in->current_char == '_')
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