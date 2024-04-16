/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:26:49 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/04 10:26:51 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*static void	reset_quotations(t_input *in)
{
	skip_spaces(in);
	if (in->current_char == '\"' && in->quotations == 2)
	{
		in->quotations = 0;
		get_next_char(in);
	}
	else if (in->current_char == '\'' && in->quotations == 1)
	{
		in->quotations = 0;
		get_next_char(in);
	}
}

static void	handle_quot_marks(t_token *next_token, t_input *in)
{
	if (in->quotations == 2 && in->current_char != '\"' && in->current_char != '$')
	{
		get_quotation_tokens(in, next_token);
	}
	else if (in->quotations == 1 && in->current_char != '\'')
	{
		get_quotation_tokens(in, next_token);
	}
	else if (in->current_char == '\"' && in->quotations == 0)
	{
		in->quotations = 2;
		get_next_char(in);
		get_quotation_tokens(in, next_token);
	}
	else if (in->current_char == '\'' && in->quotations == 0)
	{
		in->quotations = 1;
		get_next_char(in);
		get_quotation_tokens(in, next_token);
	}
}

static void	handle_control_chars(t_token *next_token, t_input *in)
{
	if (in->current_char == '|')
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
			get_variable_value(next_token, in);
		}
	}
	else if (in->current_char == '<')
	{
		if (peek_next_char(*in) == '<')
			init_token(next_token, in, "<<", READ_DELIM);
		else
			init_token(next_token, in, "<", REDIRECT_IN);
	}
	handle_more_control_chars(next_token, in);
}

static void	handle_more_control_chars(t_token *next_token, t_input *in)
{
	if (in->current_char == '>')
	{
		if (peek_next_char(*in) == '>')
			init_token(next_token, in, ">>", APPEND_OUT);
		else
			init_token(next_token, in, ">", REDIRECT_OUT);
	}
	else if (in->current_char == '&' && peek_next_char(*in) == '&')
		init_token(next_token, in, "&&", AND);
	else if (in->current_char == '-' && peek_next_char(*in) == 'n')
		init_token(next_token, in, "-n", FLAG);
}*/

/*void	get_next_token(t_token *next_token, t_input *in)
{
	skip_spaces(in);
	in->token_initialized = 0;
	//general case, we're outside of quotation marks
	if (in->current_char != '\"' && in->current_char != '$' && in->quotations == 2)
		double_quote_literal(next_token, in);
	else if (in->current_char != '\"' && in->current_char != '\'' && in->quotations == 0)
	{
		if (in->current_char == '|')
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
				get_variable_value(next_token, in);
			}
		}
		else if (in->current_char == '<')
		{
			if (peek_next_char(*in) == '<')
				init_token(next_token, in, "<<", READ_DELIM);
			else
				init_token(next_token, in, "<", REDIRECT_IN);
		}
		//handle_control_chars(next_token, in);
		else if (in->current_char == '>')
		{
			if (peek_next_char(*in) == '>')
				init_token(next_token, in, ">>", APPEND_OUT);
			else
				init_token(next_token, in, ">", REDIRECT_OUT);
		}
		else if (in->current_char == '&' && peek_next_char(*in) == '&')
			init_token(next_token, in, "&&", AND);
		else if (in->current_char == '-' && peek_next_char(*in) == 'n')
			init_token(next_token, in, "-n", FLAG);
	}
	//if we encounter an opening single quote not being inside double
	else if (in->current_char == '\'' && in->quotations == 0)
	{
		in->quotations = 1;
		single_quote_literal(next_token, in);
		//parse a literal inside single-quotes
	}
	//we encounter a closing single quote outside double
	else if (in->current_char == '\'' && in->quotations == 1)
	{
		//close the quote
		in->quotations = 0;
		get_next_char(in);
	}
	//we encounter an opening double quote outside of single
	else if (in->current_char == '\"' && in->quotations == 0)
	{
		in->quotations = 2;
		double_quote_literal(next_token, in);
		//parse a literal until $ encountered
		//unwrap the variable
		//parse until the closing quote
	}
	//we encounter a closing double quote
	else if (in->current_char == '\"' && in->quotations == 2)
	{
		in->quotations = 0;
		get_next_char(in);
		//close the quotes
	}
	else
		get_char_sequence(in, next_token);
}

void	single_quote_literal(t_token *next_token, t_input *in)
{
	char	*seq;
	int		start;

	start = in->current_position;
	while (in->current_char != '\'')
		get_next_char(in);
	seq = ft_substr(in->input, start, in->current_position - start);
	if (!seq)
		return ;
	if (ft_strlen(seq))
		init_token(next_token, in, seq, LITERAL);
}

void	double_quote_literal(t_token *next_token, t_input *in)
{
	char	*seq;
	int		start;

	start = in->current_position;
	while (in->current_char != '\"' && in->current_char != '$')
		get_next_char(in);
	seq = ft_substr(in->input, start, in->current_position - start);
	if (!seq)
		return ;
	if (ft_strlen(seq))
		init_token(next_token, in, seq, LITERAL);
}*/