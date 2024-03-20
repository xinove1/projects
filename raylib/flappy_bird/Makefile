##
# Game
#
# @file
# @version 0.1
NAME= game

#LIBFT = ./../../libft

MY_LIB= ../../mylibc

CC= gcc

#-Wall -Wextra -Werror
CFLAGS= -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

RM= rm -f

SRC= $(wildcard src/*.c)

OBJ=$(notdir $(SRC:.c=.o))

$(NAME): $(SRC) src/game.h
	@make -C $(MY_LIB)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(OBJ) $(MY_LIB)/mylib.a $(CFLAGS) -o $(NAME)

e: $(NAME)
	./$(NAME)

all: $(NAME)

clean:
	@make -C $(MY_LIB) clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C $(MY_LIB) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean

# end
