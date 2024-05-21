/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_for_exit_st.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:32:20 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/21 11:33:59 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_FOR_EXIT_ST_H
# define PARSING_FOR_EXIT_ST_H

# include "minishell.h"

char		*expand_variable(t_input *in, int state, t_exe *b);
int			process_variable(t_input *in, int start, char **res, t_exe *b);
int			preprocess_env(t_input *in, t_exe *b);
int			process_input(t_input *in, char **res, t_exe *b);
char		*expand_question_mark(t_input *in, t_exe *b);
t_ast		*parse(char *input_string, t_exe *b);

#endif