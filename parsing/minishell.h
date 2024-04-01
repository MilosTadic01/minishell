/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:35:37 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/01 18:53:53 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "tokens.h"

typedef struct s_token
{
	char	*value;
	int		token_type;
}	t_token;

typedef struct s_input
{
	char	*input;
	char	current_char;
	int		current_position;
	int		quotations;
}	t_input;

t_input	lex_input(char *string);
void	get_next_char(t_input *in);
char	peek_next_char(t_input in);
void	get_next_token(t_token *next_token, t_input *in);
void	skip_spaces(t_input *in);
void	get_char_sequence(t_input *in, t_token *next_token);
int		match_builtin(char *seq);
int		is_control_char(t_input in);
void	get_quotation_tokens(t_input *in, t_token *next_token);

void	get_variable_token(t_token *next_token, t_input *in);


#endif