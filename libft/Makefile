# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 15:45:07 by dzubkova          #+#    #+#              #
#    Updated: 2024/05/02 11:14:43 by dzubkova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = \
		ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memmove.c \
		ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
		ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_memcpy.c ft_atoi_long.c \
		ft_isspace.c ft_max.c ft_strappend.c ft_rm_consec_spaces.c ft_concat.c \
		ft_strcmp.c ft_isplusminus.c

BSRS = \
		ft_lstnew.c ft_lstsize.c ft_lstadd_front.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstdrop_back.c

OFILES = $(SRCS:.c=.o)
BOFILES = $(BSRS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

bonus: $(OFILES) $(BOFILES)
	ar rcs $(NAME) $(BOFILES) $(OFILES)

%.o: %.c
	cc -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OFILES) $(BOFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: libft.a
	cc test.c libft.a -o test

.PHONY: all bonus clean fclean re test
