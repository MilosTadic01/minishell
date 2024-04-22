/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:32:27 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/18 17:34:21 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokens.h"
# include "minishell.h"

enum e_tag
{
	COMMAND,
	BINOP
};

enum e_binop
{
	PIPE_OP = 1,
	AND_OP,
	OR_OP
};

struct s_command
{
	char	**args;
	int		size;

	t_list	*ins;
	t_list	*outs;
};

struct s_statement
{
	enum e_tag tag;

	struct s_command *command; //if tag = 0

	enum e_binop op; //if tag = 1
	struct s_statement *left;
	struct s_statement *right;
};

char				**append_token(char **command, t_list *next, int size);
int					is_literal(t_list *token_list);
struct s_statement	*new_binop(int op, struct s_statement **left, struct s_statement **right);
//struct s_statement	*parse_basic_command(t_list **token_list);
struct s_statement	*parse_command(t_list **token_list);
struct s_statement	*parse_statement(t_list **token_list);
//struct s_statement	*new_command(char **instructions, int size);
t_list				*peek_token(t_list *token_list);
t_list				*pop_token(t_list **token_list);
//void				new_redirection(t_list **token_list, struct s_command **command);
void	append_redir(struct s_command **command, struct s_redir_item *item);

#endif