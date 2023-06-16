##
# Game
#
# @file
# @version 0.1
NAME= game

LIBFT = ./../../libft

CC= gcc

CFLAGS= -Wall -Wextra -Werror -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

RM= rm -f

SRC= main.c

OBJ=$(SRC:.c=.o)

$(NAME): $(SRC) game.h
	@make -C $(LIBFT)
	@make -C $(LIBFT) bonus
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(OBJ) $(LIBFT)/libft.a $(CFLAGS) -o $(NAME)

all: $(NAME)

clean:
	@make -C $(LIBFT) clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C $(LIBFT) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean

# end
