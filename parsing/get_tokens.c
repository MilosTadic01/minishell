/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:47:31 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/11 14:35:00 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_quotes(t_input *in, int *flag)
{
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
	else
		*flag = 0;
}

void	get_quotes_literals(t_token *next_token, t_input *in, int *flag)
{
	if (in->quotations == 2 && in->current_char != '\"' && in->current_char != '$')
	{
		get_quotation_tokens(in, next_token);
		*flag = 1;
	}
	else if (in->quotations == 1 && in->current_char != '\'')
	{
		get_quotation_tokens(in, next_token);
		*flag = 1;
	}
	else if (in->current_char == '\"' && in->quotations == 0)
	{
		in->quotations = 2;
		get_next_char(in);
		get_quotation_tokens(in, next_token);
		*flag = 1;
	}
	else if (in->current_char == '\'' && in->quotations == 0)
	{
		in->quotations = 1;
		get_next_char(in);
		get_quotation_tokens(in, next_token);
		*flag = 1;
	}
}

void	get_pipes_variables(t_token *next_token, t_input *in, int *flag)
{
	if (in->current_char == '|')
	{
		if (peek_next_char(*in) == '|')
		{
			init_token(next_token, in, "||", OR);
			get_next_char(in);
		}
		else
			init_token(next_token, in, "|", PIPE);
		get_next_char(in);
		*flag = 1;
	}
	else if (in->current_char == '$')
	{
		if (peek_next_char(*in) == '?')
		{
			init_token(next_token, in, "$?", EXIT_STATUS);
			get_next_char(in);
			get_next_char(in);
		}
		else
		{
			get_next_char(in);
			get_variable_value(next_token, in);
		}
		*flag = 1;
	}
}

void	get_redirections(t_token *next_token, t_input *in, int *flag)
{
	if (in->current_char == '<')
	{
		if (peek_next_char(*in) == '<')
		{
			init_token(next_token, in, "<<", REDIRECT_IN_IN);
			get_next_char(in);
		}
		else
			init_token(next_token, in, "<", REDIRECT_IN);
		get_next_char(in);
		*flag = 1;
	}
	else if (in->current_char == '>')
	{
		if (peek_next_char(*in) == '>')
		{
			init_token(next_token, in, ">>", REDIRECT_OUT_OUT);
			get_next_char(in);
		}
		else
			init_token(next_token, in, ">", REDIRECT_OUT);
		get_next_char(in);
		*flag = 1;
	}
}

void	get_and_option(t_token *next_token, t_input *in, int *flag)
{
	if (in->current_char == '&' && peek_next_char(*in) == '&')
	{
		init_token(next_token, in, "&&", AND);
		get_next_char(in);
		*flag = 1;
	}
	else if (in->current_char == '=')
	{
		init_token(next_token, in, "=", EQUALS);
		get_next_char(in);
		*flag = 1;
	}
}