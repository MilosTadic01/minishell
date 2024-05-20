# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 12:28:47 by dzubkova          #+#    #+#              #
#    Updated: 2024/05/20 17:12:25 by dzubkova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OFILES = $(FILES:.c=.o)
LEXD = ./sources/parsing/lex/
PARSED = ./sources/parsing/parse/
BUILTINSD = ./sources/builtins/
EXECD =	./sources/execution/
INCLUDESD = ./includes/
LIBFTD = ./libft/
HFILES = $(INCLUDESD)minishell.h \
		$(INCLUDESD)lexer.h \
		$(INCLUDESD)parser.h \
		$(INCLUDESD)builtins.h \
		$(INCLUDESD)exec.h
FILES = $(LEXD)lexer.c \
		$(LEXD)lexer_utils.c \
		$(LEXD)literal_tokens.c \
		$(LEXD)quotation_status.c \
		$(LEXD)special_char_tokens.c \
		$(LEXD)recursive_tokens.c \
		$(LEXD)expansion.c \
		$(LEXD)preprocessing.c \
		$(PARSED)parser.c \
		$(PARSED)new_branches.c \
		$(PARSED)parser_utils.c \
		$(PARSED)free_ast.c \
		$(PARSED)signals.c \
		$(PARSED)parse_command_utils.c \
		$(BUILTINSD)init_env.c \
		$(BUILTINSD)echo.c \
		$(BUILTINSD)cd.c \
		$(BUILTINSD)pwd.c \
		$(BUILTINSD)export.c \
		$(BUILTINSD)unset.c \
		$(BUILTINSD)printnget_env.c \
		$(BUILTINSD)exit.c \
		$(EXECD)exec_main.c \
		$(EXECD)heredoc_boss.c \
		$(EXECD)heredoc_count_n_fetch.c \
		$(EXECD)heredoc_prompting.c \
		$(EXECD)init_exe_bus.c \
		$(EXECD)exec_utils.c \
		$(EXECD)exec_builtin.c \
		$(EXECD)exec_bin.c \
		$(EXECD)bin_prep_execve_args.c \
		$(EXECD)bin_path_setup.c \
		$(EXECD)traversal.c \
		$(EXECD)traversal_utils.c \
		$(EXECD)redir_setup.c \
		$(EXECD)redir_ins_setup.c \
		$(EXECD)redir_outs_setup.c \
		$(EXECD)redir_duping_child.c \
		$(EXECD)redir_utils.c \
		$(EXECD)pipeline_setup.c \
		$(EXECD)pipe_fu_parent.c \
		$(EXECD)pipe_fu_children.c \
		$(EXECD)wait_pipeline.c \
		main.c

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g
MAKE = make

all: libft $(NAME)

libft:
	$(MAKE) -sC $(LIBFTD) bonus

$(NAME): $(OFILES) $(HFILES)
	cc $(CFLAGS) $(OFILES) -I$(INCLUDESD) -L$(LIBFTD) -L/opt/homebrew/opt/readline/lib -lft -lreadline -lhistory -o $(NAME)

%.o: %.c $(HFILES)
	cc -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OFILES)
	$(MAKE) clean -C $(LIBFTD)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFTD)

re: fclean all

.PHONY: all clean re fclean libft