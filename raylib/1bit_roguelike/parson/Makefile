NAME=parson.a

CC=gcc

WINDOWS_TOOLs= x86_64-w64-mingw32

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC= parson.c

OBJ=$(SRC:.c=.o)

$(NAME): $(SRC) parson.h
	$(CC) $(CFLAGS) -c $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all: $(NAME)

windows: $(SRC) parson.h
	x86_64-w64-mingw32-gcc $(CFLAGS) -c $(SRC)
	x86_64-w64-mingw32-ar rc $(NAME) $(OBJ)
	x86_64-w64-mingw32-ranlib $(NAME)
	# $(WINDOWS_TOOLS)-gcc $(CFLAGS) -c $(SRC)
	# $(WINDOWS_TOOLS)-ar rc $(NAME) $(OBJ)
	# $(WINDOWS_TOOLS)-ranlib $(NAME)

web: $(SRC) parson.h
	emcc $(CFLAGS) -c $(SRC)
	emar rc $(NAME) $(OBJ)
	emranlib $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
