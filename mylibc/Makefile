NAME=mylib.a

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC= list.c arenas.c

OBJ=$(SRC:.c=.o)

$(NAME): $(SRC) libft.h
	$(CC) $(CFLAGS) -c $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all: $(NAME)

test: all
	$(CC) tests.c $(NAME) -fsanitize=address -o tests
	./tests

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
