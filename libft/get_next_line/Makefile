CC	= cc
CFLAGS	= -Wall -Wextra -Werror -g
NAME	= gnl.a
HEADER	= get_next_line.h
SRC 	= get_next_line.c \
	  get_next_line_utils.c
OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $^

$(OBJ): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all re clean fclean
