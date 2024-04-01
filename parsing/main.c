/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:28:45 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/01 19:00:07 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*input;
	t_input	in;
	t_token token;

	input = "echo $m_9 \"'a$aa'\" mm";
	in = lex_input(input);
	//int n = 5;
	while (in.current_char)
	{
		get_next_token(&token, &in);
		printf("%s %d\n", token.value, token.token_type);
	}
	return (0);
}

/*if char == '\"' && !quote:
	while (!$)
		get next
	make_string;
	go back & have the $ token from other branch;
if char == '\"' && quote
	!quote*/