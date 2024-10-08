/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:23:35 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/20 17:32:17 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_input
{
	char	*input;
	char	current_char;
	int		current_position;
	int		quotations;
	t_token	current_token;
}	t_input;

char		*get_literal_part(t_input *in);
char		*get_quotation_sequence(t_input *in);
char		peek_char(t_input *in);
int			continue_processing(t_input *in, char **res);
int			create_token(t_input *in);
int			exit_loop_conditions(t_input *in);
int			init_token(t_token *new_token, char *value, int type);
int			is_control_char(t_input *in);
int			is_literal_end(t_input *in);
int			is_logical_operator(t_input *in);
int			get_ampersand_token(t_input *in);
int			get_input_redir_token(t_input *in);
int			get_literal_token(t_input *in);
int			get_output_redir_token(t_input *in);
int			get_pipe_token(t_input *in);
int			get_recursive_token(t_input *in);
int			get_subshell_token(t_input *in);
int			quotation_status(t_input *in);
int			unclosed_parenthesis_check(t_input *in);
int			unclosed_quotations_check(t_input *in);
void		init_input(t_input *in, char *input_string);
void		next_char(t_input *in);
void		set_q_status_parenthesis(int *q_status, char copy);
void		skip_spaces(t_input *in);

#endif