/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daria <daria@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:23:38 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/16 16:44:47 by daria            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_input in;
	t_token *t;
	char *i;
	i = malloc(100);
	fgets(i, 100, stdin);
	i = ft_strtrim(i, " ");
	in.input = i;
	in.current_position = 0;
	in.current_char = *i;
	in.quotations = DEFAULT;
	while ((t = create_token(&in)))
	{	
		printf("%s\n", t->value);
	}
	return (0);
}

