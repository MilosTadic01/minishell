/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:23:35 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/17 14:30:14 by dzubkova         ###   ########.fr       */
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
}	t_input;


int	quotation_status(t_input *in);
int	unclosed_quotations_check(t_input *in);
t_token	*create_token(t_input *in);
t_token	*get_literal_token(t_input *in);
char	*get_literal_part(t_input *in);
char	*expand_variable(t_input *in, int state);
t_token	*get_output_redir_token(t_input *in);
t_token	*get_ampersand_token(t_input *in);
t_token	*get_input_redir_token(t_input *in);
t_token	*get_pipe_token(t_input *in);
void	next_char(t_input *in);
void	skip_spaces(t_input *in);
t_token	*new_token(char *value, int type);
char	peek_char(t_input *in);
int	is_control_char(t_input *in);
char	*get_quotation_sequence(t_input *in);
void	extract_tokens(char *input_string);
t_input	*new_input(char *input_string);

#endif