/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:30:37 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/25 11:20:04 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

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

typedef struct s_command
{
	char	**args; //cat file3
	int		size; //1

	t_list	*ins; //item->type = smth, item->file = file1; item->type = smth, item = file2
	t_list	*outs; // NULL
}	t_command;

typedef struct s_ast
{
	enum e_tag			tag;

	struct s_command	*command;

	enum e_binop		op;
	struct s_ast		*left;
	struct s_ast		*right;
}	t_ast;

char			*redir_filename(t_input *in);
int				is_final(t_input *input);
int				is_redirection(int type);
t_ast			*new_binop(int op, t_ast **left, t_ast **right);
t_ast			*new_command(void);
t_ast			*parse(char *input_string);
t_ast			*parse_command(t_input *in);
t_ast			*parse_statement(t_input *input);
t_redir_item	*new_item(int type, char *filename);
void			advance_token(t_input *in);
void			append_item(int type, char *filename, t_ast **ast);
void			free_item_list(t_list **lst);
void			free_ast(t_ast *s);
