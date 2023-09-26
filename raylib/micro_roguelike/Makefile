NAME= romicro

CC= gcc

CFLAGS= #-Wall -Wextra -Werror

RFLAGS= -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

RM= rm -f

SRC= main.c update.c render.c

OBJ=$(SRC:.c=.o)

$(NAME): $(addprefix src/, $(SRC)) src/game.h
	$(CC) $(CFLAGS) -c $(addprefix src/, $(SRC))
	$(CC) $(OBJ) $(CFLAGS) $(RFLAGS) -o $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean

# end
