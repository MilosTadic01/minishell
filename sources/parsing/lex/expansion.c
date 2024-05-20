/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:57:33 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/20 17:15:42 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*expand_variable(t_input *in, int state, t_exe *b)
{
	char	*var_name;
	char	*var_value;
	int		start;

	next_char(in);
	start = in->current_position;
	if (in->current_char == QUESTION_MARK)
		return (expand_question_mark(in, b));
	while (ft_isalnum(in->current_char) || in->current_char == UNDERSCORE)
		next_char(in);
	var_name = ft_substr(in->input, start, in->current_position - start);
	var_value = ft_getenv(var_name, *(b->env));
	if (var_value && !state)
		var_value = ft_rm_consec_spaces(var_value);
	else if (var_value && state)
		var_value = ft_strdup(var_value);
	else
		var_value = ft_strdup("");
	free(var_name);
	return (var_value);
}

char	*expand_question_mark(t_input *in, t_exe *b)
{
	int		copy;

	next_char(in);
	copy = g_exit;
	if (g_exit)
	{
		g_exit = 0;
		return (ft_itoa(copy));
	}
	return (ft_itoa(b->exit_st));
}
