# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 12:28:47 by dzubkova          #+#    #+#              #
#    Updated: 2024/04/22 14:18:19 by dzubkova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = lex/lexer.c lex/lexer_utils.c lex/literal_tokens.c lex/quotation_status.c \
		lex/special_char_tokens.c main.c parse/parser.c parse/new_branches.c parse/parser_utils.c
OFILES = $(FILES:.c=.o)
HFILES = minishell.h lex/lexer.h parse/parser.h

NAME = minishell

CFLAGS = -Wall -Wextra -Werror
MAKE = make

all: $(NAME)

$(NAME): $(OFILES) $(HFILES)
	$(MAKE) bonus -C ./libft
	cc $(CFLAGS) $(OFILES) libft/libft.a -o $(NAME)

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