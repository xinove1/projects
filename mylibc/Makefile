NAME=mylib.a

CC=gcc
WINDOWS_TOOLs= x86_64-w64-mingw32

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC= list.c arenas.c

OBJ=$(SRC:.c=.o)

$(NAME): $(SRC) libft.h
	$(CC) $(CFLAGS) -c $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all: $(NAME)

windows: $(SRC) libft.h
	x86_64-w64-mingw32-gcc $(CFLAGS) -c $(SRC)
	x86_64-w64-mingw32-ar rc $(NAME) $(OBJ)
	x86_64-w64-mingw32-ranlib $(NAME)
	# $(WINDOWS_TOOLS)-gcc $(CFLAGS) -c $(SRC)
	# $(WINDOWS_TOOLS)-ar rc $(NAME) $(OBJ)
	# $(WINDOWS_TOOLS)-ranlib $(NAME)

test: all
	$(CC) tests.c $(NAME) -fsanitize=address -o tests
	./tests

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
