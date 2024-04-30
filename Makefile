# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 12:28:47 by dzubkova          #+#    #+#              #
#    Updated: 2024/04/29 12:58:45 by dzubkova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OFILES = $(FILES:.c=.o)
LEXD = ./sources/parsing/lex/
PARSED = ./sources/parsing/parse/
EXECD =	./sources/execution/
BUILTINSD = ./sources/builtins/
INCLUDESD = ./includes/
LIBFTD = ./libft/
HFILES = $(INCLUDESD)minishell.h \
		$(INCLUDESD)lexer.h \
		$(INCLUDESD)parser.h \
		$(INCLUDESD)exec.h
FILES = $(LEXD)lexer.c \
		$(LEXD)lexer_utils.c \
		$(LEXD)literal_tokens.c \
		$(LEXD)quotation_status.c \
		$(LEXD)special_char_tokens.c \
		$(PARSED)parser.c \
		$(PARSED)new_branches.c \
		$(PARSED)parser_utils.c \
		$(PARSED)free_ast.c \
		$(PARSED)signals.c \
		$(BUILTINSD)env.c \
		$(BUILTINSD)export.c \
		$(BUILTINSD)unset.c \
		main.c
#		$(EXECD)exec.c \
#		$(EXECD)heredoc.c \


NAME = minishell

CFLAGS = -Wall -Wextra -Werror
MAKE = make

all: $(NAME)

$(NAME): $(OFILES) $(HFILES)
	$(MAKE) bonus -C $(LIBFTD)
	cc $(CFLAGS) $(OFILES) $(LIBFTD)libft.a -lreadline -lhistory -o $(NAME)

%.o: %.c $(HFILES)
	cc -c $(CFLAGS) -g $< -o $@

clean:
	rm -f $(OFILES)
	$(MAKE) clean -C ./libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean re fclean bonus