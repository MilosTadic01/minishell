/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:23:38 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/12 17:47:03 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_input in;
	t_token *t;
	char *i = "\"aa| \'dd\'\"|\"$HOME\"bb\'cc\'";
	in.input = i;
	in.current_position = 0;
	in.current_char = *i;
	in.quotations = DEFAULT;
	t = get_literal_token(&in);
	return (0);
}

