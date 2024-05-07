/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:30:37 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/07 15:48:54 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

enum e_tag
{
	COMMAND,
	BINOP,
	SUBSHELL
}	;

enum e_binop
{
	PIPE_OP = 1,
	AND_OP,
	OR_OP
}	;

typedef struct s_command
{
	char	**args; //cat file3
	int		size; //1

	t_list	*ins; //item->type = smth, item->filename = file1; item->type = smth, item = file2
	t_list	*outs; // NULL
}	t_command;

typedef struct s_ast
{
	enum e_tag			tag;

	char				*subshell_cmd;

	struct s_command	*command;

	enum e_binop		op;
	struct s_ast		*left;
	struct s_ast		*right;
}	t_ast;

char			*redir_filename(t_input *in, t_list **env);
int				is_command_separator(t_input *input);
int				is_final_token(t_input *input);
int				is_redirection(int type);
t_ast			*new_binop(int op, t_ast **left, t_ast **right);
t_ast			*new_command(void);
t_ast			*new_subshell(char *value);
t_ast			*parse(char *input_string, t_list **env);
t_ast			*parse_command(t_input *in, t_list **env);
t_ast			*parse_pipe(t_input *input, t_list **env);
t_ast			*parse_statement(t_input *input, t_list **env);
t_ast			*parse_subshell(t_input *input, t_list **env);
t_redir_item	*new_item(int type, char *filename);
int				advance_token(t_input *in, t_list **env);
void			append_item(int type, char *filename, t_ast **ast);
void			free_ast(t_ast *s);
void			free_item_list(t_list **lst);
void			free_str(char **str, int size);
void			handle_command_argument(t_input *input, t_ast **ast);
int				handle_redirection(t_input *input, t_list **env, t_ast **ast);
void			prompt(char *subcmd, t_list **env);
void			receive_signals(void);
void			sighandler(int signum);
