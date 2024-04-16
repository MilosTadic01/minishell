/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:35:37 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/11 11:33:18 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "tokens.h"

typedef struct s_input
{
	char	*input;
	char	current_char;
	int		current_position;
	int		quotations;
	int		token_initialized;
}	t_input;

t_list	*lex_input(char *string);
void	get_next_char(t_input *in);
char	peek_next_char(t_input in);
void	get_next_token(t_token *next_token, t_input *in);
void	skip_spaces(t_input *in);
void	get_char_sequence(t_input *in, t_token *next_token);
int		match_builtin(char *seq);
int		is_control_char(t_input in);
void	get_quotation_tokens(t_input *in, t_token *next_token);
t_input	initialize_input(char *command_string);
void	get_and_option(t_token *next_token, t_input *in, int *flag);
void	get_char_sequence(t_input *in, t_token *next_token);
void	get_next_token(t_token *next_token, t_input *in);
void	get_quotes_literals(t_token *next_token, t_input *in, int *flag);
void	get_pipes_variables(t_token *next_token, t_input *in, int *flag);
void	get_redirections(t_token *next_token, t_input *in, int *flag);
void	get_quotation_tokens(t_input *in, t_token *next_token);
void	get_variable_value(t_token *next_token, t_input *in);
void	init_token(t_token *new_token, t_input *in, char *value, int type);
void	reset_quotes(t_input *in, int *flag);

#endif