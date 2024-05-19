/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:23:40 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/17 14:38:16 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "lexer.h"
# include "structs.h"
# include "parser.h"
# include "errors.h"
# include "exec.h"
# include "builtins.h"

extern int	g_exit;

# define _XOPEN_SOURCE 700
# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

void	minishell(char *subcmd, t_exe *b, t_list **my_env);
void	prompt(char *subcmd, t_exe *b, t_list **env);

# define PIPE 124
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define AMPERSAND 38
# define REDIRECT_IN 60
# define REDIRECT_OUT 62
# define DOLLAR 36

# define REDIRECT_OUT_OUT 6262
# define REDIRECT_IN_IN 6060
# define AND 3838
# define OR 124124
# define EXIT_STATUS 14

# define ECHO 100
# define CD 101
# define PWD 102
# define EXPORT 103
# define UNSET 104
# define ENV 105
# define EXIT 106

# define LITERAL 200
# define FINAL_TOKEN 300
# define SUBSHELL 4242
# define RECCALL 4224

# define DEFAULT 0
# define SUCCESS 0

# define UNDERSCORE 95
# define QUESTION_MARK 63

# define OPEN_PARENTHESE 40
# define CLOSE_PARENTHESE 41

#endif