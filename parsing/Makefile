# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 12:28:47 by dzubkova          #+#    #+#              #
#    Updated: 2024/04/01 19:03:07 by dzubkova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = main.c lexer.c
OFILES = $(FILES:.c=.o)
HFILES = tokens.h minishell.h

NAME = minishell

CFLAGS = -Wall -Wextra -Werror
MAKE = make

all: $(NAME)

$(NAME): $(OFILES) $(HFILES)
	$(MAKE) bonus -C ./libft
	cc $(CFLAGS) $(OFILES) libft/libft.a -o $(NAME)

%.o: %.c $(HFILES)
	cc -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OFILES)
	$(MAKE) clean -C ./libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean re fclean bonus